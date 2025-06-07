#include "../inc/Server.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

Server	*g_servPtr = nullptr;

// Server::Server()
// :	cfg_{},
// 	listenSo_{},
// 	accepting_{false},
// 	running_{false},
// 	cmds_{
// 		{"NICK",  [this](int fd, const t_data d) { cmdNick(fd, d); }},
// 		{"USER", [this](int fd, const t_data d) { cmdUser(fd, d); }},
// 		{"JOIN", [this](int fd, const t_data d) { cmdJoin(fd, d); }},
// 		{"MODE", [this](int fd, const t_data d) { cmdMode(fd, d); }},
// 		{"PING", [this](int fd, const t_data d) { cmdPing(fd, d); }},
// 		{"KICK", [this](int fd, const t_data d) { cmdKick(fd, d); }},
// 		{"TOPIC", [this](int fd, const t_data d) { cmdTopic(fd, d); }},
// 		{"PRIVMSG", [this](int fd, const t_data d) { cmdPrivMsg(fd, d); }},
// 		{"INVITE", [this](int fd, const t_data d) { cmdInvite(fd, d); }},
// 		{"PART", [this](int fd, const t_data d) { cmdPart(fd, d); }},
// 	}
// {}

Server::Server(Config&& cfg)
:	cfg_{std::move(cfg)},
	listenSo_{},
	ircMsgDelimiter_{cfg.getMsgDelimiter()},
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
{}

Server::Server(Server&& other)
:	cfg_(std::move(other.cfg_)),
	listenSo_(std::move(other.listenSo_)),
	ip_(std::move(other.ip_)),
	host_(std::move(other.host_)),
	accepting_{other.accepting_},
	running_{other.running_},
	clients_(std::move(other.clients_)),
	pollFds_(std::move(other.pollFds_)),
	channels_(std::move(other.channels_)),
	cmds_{std::move(other.cmds_)}
{}

/*
	-We stop server only if we run out of resources (std::bad_alloc or poll() says EINVAL or ENOMEM AND we have no clients)
*/
void Server::run() {
	listenSo_.initListener(cfg_.getPort());
	pollFds_.reserve(POLLFD_VEC_DEFAULT_INIT_SIZE);
	pollFds_.push_back({listenSo_.getFd(), POLLIN, 0});
	resolveHost();

	accepting_ = true;
	running_ = true;

	std::cout << GREENIRC << "Server started on host " << host_ << " and port " << cfg_.getPort() << RESETIRC
		<< "\nUse irssi and command '/connect <hostname> <port> <password>' to connect" << std::endl;

	while (running_) {
		try {
			if (poll(pollFds_.data(), pollFds_.size(), -1) < 0) {
				if (errno == EINVAL || errno == ENOMEM) {
					if (clients_.empty()) {
						running_ = false;
					}
					rmClient(pollFds_.back().fd);
					accepting_ = false;
				}
				std::cerr << "poll() returned -1 with errno: " << strerror(errno) << std::endl;
				continue;
			}
			#ifdef IRC_POLL_PRINTS
				std::cout << "We poll" << std::endl;
			#endif
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
		#ifdef IRC_POLL_PRINTS
			std::cout << "POll-- i=" << i << " size of pollFds_=" << pollFds_.size() << std::endl;
		#endif
		pollfd&	pfd = pollFds_.at(i);

		if (POLLIN & pfd.revents) {
			#ifdef IRC_POLL_PRINTS
				std::cout << "POLLIN--" << std::endl;
			#endif
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
			#ifdef IRC_POLL_PRINTS
				std::cout << REDIRC << "POLL ERRS--" << RESETIRC << std::endl;
			#endif
			std::cerr << REDIRC << "POLL ERRS" << RESETIRC << strerror(errno) << " revents: " << pfd.revents << " on fd " << pfd.fd << std::endl;
			rmClient(pfd.fd);
		} else if (POLLOUT & pfd.revents) {
			#ifdef IRC_POLL_PRINTS
				std::cout << "POLLOUT--" << std::endl;
			#endif
			if (clients_.at(pfd.fd).send() == false) {
				rmClient(pfd.fd);
				continue;
			}
		}

		if (pfd.fd != listenSo_.getFd()) {
			if (clients_.at(pfd.fd).isInactive(cfg_.getAllowedInactivity())) {
				rmClient(pfd.fd);
			} else if (&pfd != clients_.at(pfd.fd).getPfdPtr()) {
				clients_.at(pfd.fd).setPfdPtr(&pfd);
			}
		}
	}
}

void Server::acceptNewConnection() {
	Socket	clientSock;

	if (listenSo_.accept(clientSock) == false) {
		if (errno == EMFILE || errno == ENFILE || errno == ENOMEM || errno == ENOBUFS) {
			accepting_ = false;
		} else if (errno != EAGAIN && errno != EWOULDBLOCK) {
			std::cerr << "accept4() error: " << strerror(errno) << std::endl;
		}
		return;
	}

	int fd = clientSock.getFd();
	addClient(clientSock);

	std::cout << YELLOWIRC
			<< "Accepted new connection from " 
			<< clientSock.getIpStr() << ":"//fix
			<< ntohs(clientSock.getAddr().sin_port) 
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
		clients_.emplace(fd, Client(std::move(sock), &pollFds_.back(), ircMsgDelimiter_));
		clients_.at(fd).setHostName(host_);
	} catch (std::exception& e) {
		std::cerr << "addClient to map (fd: " << fd << ") failed: " << e.what() << std::endl;
		rmClient(fd);
		return;
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

		if (clients_.at(fromFd).isAuthenticated() == false && msgs.find(ircMsgDelimiter_) != std::string::npos) {
			return processAuth(fromFd, msgs);
		} else {
			#ifdef IRC_DEBUG_PRINTS
				int ms = 50;
				// cout << YELLOWIRC << "waiting " << ms << "ms, msg: " << msgs << RESETIRC << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(ms));
			#endif
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
	#ifdef IRC_AUTH_PRINTS
		cout << GREENIRC << "authenticate() msg:" << messages << RESETIRC << endl;
	#endif
	size_t pos = 0;
	std::string msg;
	Client& newClient = clients_.at(fromFd);
	newClient.addAuthAttempt();
	int attemptsLeft = cfg_.getMaxAuthAttempts() - newClient.getAuthAttempts();

	while ((pos = messages.find(ircMsgDelimiter_)) != std::string::npos) {
		msg = messages.substr(0, pos);
		#ifdef IRC_AUTH_PRINTS
			std::cout << "msg:" << msg << std::endl;
		#endif

		if (msg.find("PASS ") == 0) {
			msg.erase(0, 5);
			#ifdef CMD_CONCAT_TEST_IRC
				if (msg.data()[msg.length() - 1] == '\r') { msg.pop_back(); }
			#endif
			#ifdef IRC_AUTH_PRINTS
				cout << "~~checking password:" << msg << " and msglen=" << msg.length() << endl;
			#endif
			if (cfg_.CheckPassword(msg) == true) {
				newClient.setPassReceived();
			} else {
				newClient.toSend(IrcMessages::wrongPass());
			}
		} else if (msg.find("NICK ") == 0) {
			cmdNick(fromFd, {msg, {}});
		} else if (msg.find("USER ") == 0) {
			cmdUser(fromFd, {msg, {}});
		} else if (msg.find("QUIT") == 0) {
			return false;
		}
		#ifdef IRC_AUTH_PRINTS
			cout << "pass attempt: " << newClient.getAuthAttempts() << endl;
		#endif
		messages.erase(0, pos + ircMsgDelimiter_.length());
	}
	if (newClient.hasReceivedPass() && newClient.hasReceivedNick() && newClient.hasReceivedUser()) {
		newClient.setAuthenticated();
		newClient.toSend(IrcMessages::welcome(newClient.getNick(), cfg_.getServName()));
	} else {
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
				<< "             recvBuf-->" << cliFd.second.getRecvBuf() << "size:" << cliFd.second.getRecvBuf().size() << endl
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

void Server::checkRegistration(int fd) {
	if (!clients_[fd].getNick().empty() && !clients_[fd].getUser().empty() && !clients_[fd].isAuthenticated()) {
		clients_[fd].setAuthenticated();  // Assuming you want to set them as authenticated
		clients_.at(fd).toSend(IrcMessages::motd());
	}
}

std::vector<std::string>	Server::tokenize(std::istringstream& cmdParams){
	std::vector<std::string> tokens;
	std::string token;
	while (cmdParams >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

std::string	Server::fetchIP() {
	int sock = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		std::cerr << "Could not create socket in fetchPublicFacingIP()" << std::endl;
		return "127.0.0.1";
	}

	sockaddr_in remoteAddr{};
	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_port = htons(80);
	inet_pton(AF_INET, "8.8.8.8", &remoteAddr.sin_addr);

	if (::connect(sock, (sockaddr*)&remoteAddr, sizeof(remoteAddr)) == -1) {
		::close(sock);
		std::cerr << "connect() failed  in fetchPublicFacingIP()" << std::endl;
		return "127.0.0.1";
	}

	sockaddr_in localAddr{};
	socklen_t len = sizeof(localAddr);
	if (getsockname(sock, (sockaddr*)&localAddr, &len) == -1) {
		::close(sock);
		std::cerr << "getsockname() failed in fetchPublicFacingIP()" << std::endl;
		return "127.0.0.1";
	}

	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &localAddr.sin_addr, ip, sizeof(ip));
	::close(sock);
	return std::string(ip);
}

void	Server::resolveHost() {
	char hostname[HOST_NAME_MAX];
	if (gethostname(hostname, HOST_NAME_MAX) != 0) {
		perror("gethostname");
		return;
	}
	host_ = std::string(hostname);
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
