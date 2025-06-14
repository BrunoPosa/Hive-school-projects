#include "../inc/Server.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

Server	*g_servPtr = nullptr;

Server::Server()
:	cfg_{},
	listenSo_{},
	listenSoFd_{-1},
	accepting_{false},
	running_{false},
	allowedInactivity_{300},
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
		{"WHO", [this](int fd, const t_data d) { extraCmdWho(fd, d); }}
	}
{
	pollFds_.reserve(MAX_CLIENTS);
}

Server::Server(Config&& cfg)
:	cfg_{std::move(cfg)},
	listenSo_{},
	listenSoFd_{-1},
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
		{"WHO", [this](int fd, const t_data d) { extraCmdWho(fd, d); }}
	}
{
	allowedInactivity_ = cfg_.getAllowedInactivity();
	pollFds_.reserve(MAX_CLIENTS);
}

Server::Server(Server&& other)
:	cfg_(std::move(other.cfg_)),
	listenSo_(std::move(other.listenSo_)),
	listenSoFd_{std::exchange(other.listenSoFd_, -1)},
	ip_(std::move(other.ip_)),
	host_(std::move(other.host_)),
	accepting_{false},
	running_{false},
	allowedInactivity_{other.allowedInactivity_},
	clients_(std::move(other.clients_)),
	pollFds_(std::move(other.pollFds_)),
	channels_(std::move(other.channels_)),
	cmds_{std::move(other.cmds_)}
{}

/*
	Server stops only on std::bad_alloc without clients, and poll() errors EINVAL / ENOMEM
*/
void	Server::run() {
	listenSo_.initListener(cfg_.getPort());
	listenSoFd_	= listenSo_.getFd();
	host_		= listenSo_.resolveHost();
	pollFds_.push_back({listenSoFd_, POLLIN, 0});

	accepting_ = true;
	running_ = true;

	std::cout << GREENIRC << "Server started on host " << host_ << " and port " << listenSo_.getPortNum() << RESETIRC
		<< "\nUse irssi and command '/connect <hostname> <port> <password>' to connect" << std::endl;

	eventLoop();

	cout << "Server shutting down.." << endl;
}

void	Server::eventLoop() {

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
}

void	Server::handleEvents() {
	for (int i = pollFds_.size() - 1; i >= 0; --i) {

		pollfd&	pfd	= pollFds_.at(i);
		int		fd	= pfd.fd;

		if (fd != listenSoFd_) {
			if (clients_.at(fd).isInactive(allowedInactivity_)) {
				rmClient(fd);
			} else if (&pfd != clients_.at(fd).getPfdPtr()) {
				clients_.at(fd).setPfdPtr(&pfd);
			}
		}

		if (POLLIN & pfd.revents) {
			if (fd == listenSoFd_) {
				if (accepting_) {
					acceptNewConnection();
				}
				continue;
			} else if (clients_.at(fd).receive() == false || handleMsgs(fd) == false) {
				rmClient(fd);
				continue;
			}
		}
		if ((POLLERR | POLLHUP | POLLNVAL) & pfd.revents) {
			std::cerr << REDIRC << "POLL ERRS" << RESETIRC << strerror(errno) << " revents: " << pfd.revents << " on fd " << fd << std::endl;
			rmClient(fd);

		} else if (POLLOUT & pfd.revents) {

			if (clients_.at(fd).send() == false) {
				rmClient(fd);
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
		clients_.emplace(fd, Client(std::move(sock), &pollFds_.back(), host_));
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
	rmClient from pollFds_ vector, clients_ map, and all of client's own joinedChannels (destroying the channels which remain empty,
	or broadcasting ClientQuit msg to all remaining members),
*/
void Server::rmClient(int rmFd) {
		for (int i = pollFds_.size() - 1; i >= 0; --i) {
			if (pollFds_.at(i).fd == rmFd) { pollFds_.erase(pollFds_.begin() + i); }
		}

		if (clients_.find(rmFd) == clients_.end()) {
			return;
		}

		Client& client = clients_.at(rmFd);

		auto&	joinedChannels = client.getJoinedChannels();
		for (const auto& [joinedChName, _] : joinedChannels) {
			auto channelIt = channels_.find(joinedChName);

			if (channelIt != channels_.end()) {
				channelIt->second.removeClient(rmFd);
				if (channelIt->second.isEmpty()) {
					channels_.erase(joinedChName);
				} else {
					channels_.at(joinedChName).broadcast(IrcMessages::clientQuit(client), client.getNick(), -1);
				}
			}
		}

		clients_.erase(rmFd);

		if (accepting_ == false) {
			accepting_ = true;//start accepting again if the server was not accepting (due to maxing out)
		}

		std::cout << "client fd:" << rmFd << " removed." << std::endl;
}

bool	Server::handleMsgs(int fromFd) {
	try {
		size_t pos = 0;
		std::string line;
		Client&	client = clients_.at(fromFd);
		std::string	delimiter(client.getDelimiter());
		std::string	msgs = client.getMsgs();

		#ifdef IRC_BUF_PRINTS
			cout << GREENIRC << "handleMsgs:" << msgs << RESETIRC << endl;
		#endif
		if (client.isAuthenticated() == false) {
			if (msgs.find('\n') != std::string::npos) {
				return processAuth(fromFd, msgs);
			}
		} else {
			while ((pos = msgs.find(delimiter)) != std::string::npos) {
				line = msgs.substr(0, pos);
				if (line.find("QUIT") == 0 || line.find("quit") == 0 ) {
					return false;
				}
				dispatchCommand(fromFd, line);
				msgs.erase(0, pos + delimiter.length());
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
	std::string	delimiter(newClient.getDelimiter());
	std::string	response;

	newClient.addAuthAttempt();
	int attemptsLeft = cfg_.getMaxAuthAttempts() - newClient.getAuthAttempts();

	while ((pos = messages.find(delimiter)) != std::string::npos) {
		msg = messages.substr(0, pos);
		if (msg.find("PASS ") == 0 || msg.find("pass ") == 0) {
			msg.erase(0, 5);
			if (cfg_.CheckPassword(msg) == true) {
				newClient.setPassReceived();
			} else {
				response += IrcMessages::wrongPass();
			}
		} else if (msg.find("NICK ") == 0 || msg.find("nick ") == 0) {
			cmdNick(fromFd, {msg, {}});
		} else if (msg.find("USER ") == 0 || msg.find("user ") == 0) {
			cmdUser(fromFd, {msg, {}});
		} else if (msg.find("QUIT") == 0 || msg.find("quit") == 0) {
			return false;
		}
		messages.erase(0, pos + delimiter.length());
	}

	if (newClient.hasReceivedPass() && newClient.hasReceivedNick() && newClient.hasReceivedUser()) {
		newClient.setAuthenticated();
		response = IrcMessages::welcome(newClient.getNick(), cfg_.getServName());
	} else {
		response += IrcMessages::attemptsLeft(attemptsLeft, newClient.getNick());
	}

	if (newClient.hasReceivedPass()) {
		newClient.toSend(response);
	} else {
		newClient.toSend(response + IrcMessages::askPass(newClient.getNick()));
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
	while (cmdParams.fail() == false && (cmdParams >> token)) {
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

void Server::ft_send(int fd, const std::string& message) {
	try {
		clients_.at(fd).toSend(message);
	} catch (std::out_of_range& e) {
		std::cerr << "clients_ map access at nonexisting key:" << fd << " - " << e.what() << std::endl;
	}
}

void	Server::extraCmdWho(int fd, const t_data data) {
	if (data.fullMsg.length() < 5) {
		return;
	}

	clients_.at(fd).toSend(RPL_ENDOFWHO(clients_.at(fd).getNick(), data.fullMsg.substr(4)));
}