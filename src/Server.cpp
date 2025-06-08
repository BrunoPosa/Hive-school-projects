#include "../inc/Server.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

Server	*g_servPtr = nullptr;

Server::Server()
:	cfg_{},
	listenSo_{},
	accepting_{false},
	running_{false},
	cmds_{
		{"NICK",  [this](int fd, const t_data d) { cmdNick(fd, d); }},
		{"USER", [this](int fd, const t_data d) { cmdUser(fd, d); }},
		{"JOIN", [this](int fd, const t_data d) { cmdJoin(fd, d); }},
		{"MODE", [this](int fd, const t_data d) { cmdMode(fd, d); }},
		{"PING", [this](int fd, const t_data d) { cmdPing(fd, d); }},
		{"KICK", [this](int fd, const t_data d) { cmdKick(fd, d); }},
		{"TOPIC", [this](int fd, const t_data d) { cmdTopic(fd, d); }},
		{"PRIVMSG", [this](int fd, const t_data d) { cmdPrivMsg(fd, d); }},
		{"INVITE", [this](int fd, const t_data d) { cmdInvite(fd, d); }},
		{"PART", [this](int fd, const t_data d) { cmdPart(fd, d); }},
	}
{
	ircMsgDelimiter_ = cfg_.getMsgDelimiter();
	pollFds_.reserve(MAX_CLIENTS);
}

Server::Server(Config&& cfg)
:	cfg_{std::move(cfg)},
	listenSo_{},
	ircMsgDelimiter_{cfg_.getMsgDelimiter()},
	accepting_{false},
	running_{false},
	cmds_{
		{"NICK",  [this](int fd, const t_data d) { cmdNick(fd, d); }},
		{"USER", [this](int fd, const t_data d) { cmdUser(fd, d); }},
		{"JOIN", [this](int fd, const t_data d) { cmdJoin(fd, d); }},
		{"MODE", [this](int fd, const t_data d) { cmdMode(fd, d); }},
		{"PING", [this](int fd, const t_data d) { cmdPing(fd, d); }},
		{"KICK", [this](int fd, const t_data d) { cmdKick(fd, d); }},
		{"TOPIC", [this](int fd, const t_data d) { cmdTopic(fd, d); }},
		{"PRIVMSG", [this](int fd, const t_data d) { cmdPrivMsg(fd, d); }},
		{"INVITE", [this](int fd, const t_data d) { cmdInvite(fd, d); }},
		{"PART", [this](int fd, const t_data d) { cmdPart(fd, d); }},
	}
{
	ircMsgDelimiter_ = cfg_.getMsgDelimiter();
	pollFds_.reserve(MAX_CLIENTS);
}

Server::Server(Server&& other)
:	cfg_(std::move(other.cfg_)),
	listenSo_(std::move(other.listenSo_)),
	ip_(std::move(other.ip_)),
	host_(std::move(other.host_)),
	ircMsgDelimiter_{std::move(other.ircMsgDelimiter_)},
	accepting_{other.accepting_},
	running_{other.running_},
	clients_(std::move(other.clients_)),
	pollFds_(std::move(other.pollFds_)),
	channels_(std::move(other.channels_)),
	cmds_{std::move(other.cmds_)}
{}

/*
	-We stop server only on std::bad_alloc without clients and poll() errors EINVAL or ENOMEM
*/
void Server::run() {
	listenSo_.initListener(cfg_.getPort());
	host_ = listenSo_.resolveHost();
	pollFds_.push_back({listenSo_.getFd(), POLLIN, 0});

	accepting_ = true;
	running_ = true;

	std::cout << GREENIRC << "Server started on host " << host_ << " and port " << cfg_.getPort() << RESETIRC
		<< "\nUse irssi and command '/connect <hostname> <port> <password>' to connect" << std::endl;

	while (running_) {
		try {
			if (poll(pollFds_.data(), pollFds_.size(), -1) < 0) {
				if (errno == EINVAL || errno == ENOMEM) {
					running_ = false;
				}
				std::cerr << "poll() returned -1 with errno: " << strerror(errno) << std::endl;
				continue;
			}
			handleEvents();

		} catch (const std::bad_alloc& e) {
			std::cerr << "Exception caught inside poll loop: " << e.what() << std::endl;
			if (clients_.empty()) {
				running_ = false;
			}
			rmClient(pollFds_.back().fd);
			accepting_ = false;
		} catch (const std::exception& e) {
			std::cerr << "Exception caught inside poll loop: " << e.what() << std::endl;
		}
	}
	cout << "Server shutting down.." << endl;
}

void Server::handleEvents() {
	for (int i = pollFds_.size() - 1; i >= 0; --i) {

		pollfd&	pfd = pollFds_.at(i);

		if (pfd.fd != listenSo_.getFd()) {
			if (clients_.at(pfd.fd).isInactive(cfg_.getAllowedInactivity())) {
				rmClient(pfd.fd);
			} else if (&pfd != clients_.at(pfd.fd).getPfdPtr()) {
				clients_.at(pfd.fd).setPfdPtr(&pfd);
			}
		}

		if (POLLIN & pfd.revents) {
			if (pfd.fd == listenSo_.getFd()) {
				if (accepting_) {
					acceptNewConnection();
				}
				continue;
			} else if (clients_.at(pfd.fd).receive() == false || handleMsgs(pfd.fd) == false) {
				rmClient(pfd.fd);
				continue;
			}
		}
		if ((POLLERR | POLLHUP | POLLNVAL) & pfd.revents) {
			std::cerr << REDIRC << "POLL ERRS" << RESETIRC << strerror(errno) << " revents: " << pfd.revents << " on fd " << pfd.fd << std::endl;
			rmClient(pfd.fd);

		} else if (POLLOUT & pfd.revents) {

			if (clients_.at(pfd.fd).send() == false) {
				rmClient(pfd.fd);
				continue;
			}
		}
	}
}

void Server::acceptNewConnection() {

	Socket	clientSock;

	if (clients_.size() >= MAX_CLIENTS) {
		return;
	}

	if (listenSo_.accept(clientSock) == false) {
		std::cerr << "accept() or fcntl() error: " << strerror(errno) << std::endl;
		if (errno == EMFILE || errno == ENFILE || errno == ENOMEM || errno == ENOBUFS) {
			accepting_ = false;
		}
		return;
	}

	int fd = clientSock.getFd();
	addClient(clientSock);

	std::cout << YELLOWIRC
			<< "Accepted new connection from "
			<< clients_.at(fd).getIP() << ":"
			<< clients_.at(fd).getPort()
			<< " (FD: " << fd << ")" << RESETIRC << std::endl;
}

//constructs Client with the given socket and adds its fd to pollFds_ and the object itself to clients_ map
void Server::addClient(Socket& sock) {
	int fd = sock.getFd();
	try {
		pollFds_.push_back({sock.getFd(), POLLIN, 0});
	} catch (std::exception& e) {
		std::cerr << "addClient to pollFds_ (fd: " << fd << ") failed: " << e.what() << std::endl;
		return;
	}
	try {
		clients_.emplace(fd, Client(std::move(sock), &pollFds_.back(), ircMsgDelimiter_, host_));
	} catch (std::exception& e) {
		std::cerr << "addClient to map (fd: " << fd << ") failed: " << e.what() << std::endl;
		rmClient(fd);
		return;
	}
	if (clients_.size() == MAX_CLIENTS) {
		accepting_ = false;
	}
}

/*
	removes Client from server's pollFds_ vector, all of client's own joinedChannels (destroying all channels which remain empty or
	broadcasting ClientQuit msg to all remaining members),
	and lastly - from the server's clients_ map
	If the IRC_ACCEPTING flag was down, this function raises it (as now there is more resources available)
*/
void Server::rmClient(int rmFd) {
	try {
		for (int i = pollFds_.size() - 1; i >= 0; --i) {
			if (pollFds_.at(i).fd == rmFd) { pollFds_.erase(pollFds_.begin() + i); }
		}

		if (clients_.find(rmFd) == clients_.end()) {
			return;
		}

		const auto&	joinedChannels = clients_.at(rmFd).getJoinedChannels();
		for (const auto& [channelName, _] : joinedChannels) {
			auto channelIt = channels_.find(channelName);

			if (channelIt != channels_.end()) {
				channelIt->second.removeClient(rmFd);
				if (channelIt->second.isEmpty()) {
					channels_.erase(channelName);
				} else {
					channels_.at(channelName).broadcast(IrcMessages::clientQuit(clients_.at(rmFd)), clients_.at(rmFd).getNick(), -1);
				}
			}
		}

		auto clientIt = clients_.find(rmFd);
		if (clientIt != clients_.end()) {
			clients_.erase(clientIt);
		}

		accepting_ = true;//start accepting again if the server was not accepting (due to maxing out)

		std::cout << "client fd:" << rmFd << " removed." << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Exception caught in rmClient(): " << e.what() << " fd: " << rmFd << std::endl;
	}
}

bool	Server::handleMsgs(int fromFd) {
	try {
		size_t pos = 0;
		std::string line;
		std::string	msgs = clients_.at(fromFd).getMsgs();

		if (clients_.at(fromFd).isAuthenticated() == false) {
			if (msgs.find(ircMsgDelimiter_) != std::string::npos) {
				return processAuth(fromFd, msgs);
			}
		} else {
			while ((pos = msgs.find(ircMsgDelimiter_)) != std::string::npos) {
				line = msgs.substr(0, pos);
				if (line.find("QUIT") == 0) {
					return false;
				}
				dispatchCommand(fromFd, line);
				msgs.erase(0, pos + ircMsgDelimiter_.length());
			}
		}
	} catch (std::exception& e) {
		std::cerr << "Exception caught in handleMsgs(): " << e.what() << "Client fd:" << fromFd << std::endl;
	}
	return true;
}

//if this returns false, client should be removed
bool	Server::processAuth(int fromFd, std::string messages) {
	size_t pos = 0;
	std::string msg;
	Client& newClient = clients_.at(fromFd);
	newClient.addAuthAttempt();
	int attemptsLeft = cfg_.getMaxAuthAttempts() - newClient.getAuthAttempts();

	while ((pos = messages.find(ircMsgDelimiter_)) != std::string::npos) {
		msg = messages.substr(0, pos);

		if (msg.find("PASS ") == 0) {
			msg.erase(0, 5);
			if (ircMsgDelimiter_ == "\n") {//for allowing concat cmd testing via netcat
				if (msg.at(msg.length() - 1) == '\r') { msg.pop_back(); }
			}
			if (cfg_.CheckPassword(msg) == true) {
				newClient.setPassReceived();
			} else {
				newClient.toSend(IrcMessages::wrongPass());
				newClient.toSend(IrcMessages::attemptsLeft(attemptsLeft, newClient.getNick()));
				newClient.toSend(IrcMessages::askPass(newClient.getNick()));
			}
		} else if (msg.find("NICK ") == 0) {
			cmdNick(fromFd, {msg, {}});
		} else if (msg.find("USER ") == 0) {
			cmdUser(fromFd, {msg, {}});
		} else if (msg.find("QUIT") == 0) {
			return false;
		}
		messages.erase(0, pos + ircMsgDelimiter_.length());
	}

	if (newClient.hasReceivedPass() && newClient.hasReceivedNick() && newClient.hasReceivedUser()) {
		newClient.setAuthenticated();
		newClient.toSend(IrcMessages::welcome(newClient.getNick(), cfg_.getServName()));
	} else if (newClient.hasReceivedPass() + newClient.hasReceivedNick() + newClient.hasReceivedUser() + newClient.getAuthAttempts() > 5) {
		newClient.toSend(IrcMessages::attemptsLeft(attemptsLeft, newClient.getNick()));
		newClient.toSend(IrcMessages::askPass(newClient.getNick()));
	}
	if (attemptsLeft <= 0) {
		return false;
	}
	return true;
}

void	Server::gracefulShutdown() {
	#ifdef IRC_ON_SHUTDOWN_PRINT
		cout << "====printout on sigint====" << endl;
		for (auto& cliFd : clients_) {
			cout << GREENIRC << "\nclient fd:" << cliFd.first << "getFd():" << cliFd.second.getFd() << "  hasDataToSend-->" << cliFd.second.hasDataToSend() << endl
				<< "             isAuthenticated-->" << cliFd.second.isAuthenticated() << endl;
			cout << "             joinedChannels:" << endl;
			for (const auto& pair : cliFd.second.getJoinedChannels()) {
				cout << "                '" << pair.first << "' bool pair -->" << pair.second << " and client isInChannel-->" << cliFd.second.isInChannel(pair.first) << RESETIRC << endl;
			}
		}

		cout << YELLOWIRC << "\n\n==channel_ members==" << endl;
		for (const auto& pair : channels_) {
			cout << "'" << pair.first << "' members:" << endl;
			for (auto& it : pair.second.getChClients()) {
				cout << "  fd: " << it << endl;
			}
		}
		cout << RESETIRC << endl;
	#endif

	running_ = false;
}

std::vector<std::string>	Server::tokenize(std::istringstream& cmdParams){
	std::vector<std::string> tokens;
	std::string token;
	while (cmdParams >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

int Server::getClientFdByNick(const std::string& nick) const {
	for (std::map<int, Client>::const_iterator it = clients_.begin(); it != clients_.end(); ++it) {
		if (it->second.getNick() == nick) {
			return it->first;
		}
	}
	return -1; // Not found
}

std::string Server::getNickByFd(int fd) const {
	std::map<int, Client>::const_iterator it = clients_.find(fd);
	if (it != clients_.end()) {
		return it->second.getNick();
	}
	return ""; // Not found
}

void Server::ft_send(int fd, const std::string& message) {
	try {
		clients_.at(fd).toSend(message);
	} catch (std::out_of_range& e) {
		std::cerr << "clients_ map access at nonexisting key:" << fd << " - " << e.what() << std::endl;
	}
}
