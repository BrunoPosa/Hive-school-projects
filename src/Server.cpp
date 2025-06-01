#include "../inc/Server.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

Server	*g_servPtr = nullptr;

Server::Server()
:	cfg_{},
	listenSo_{},
	state_{0}
{}

Server::Server(Config&& cfg)
:	cfg_{std::move(cfg)},
	listenSo_{},
	state_{0}
{}

Server::Server(Server&& other)
:	cfg_(std::move(other.cfg_)),
	listenSo_(std::move(other.listenSo_)),
	ip_(std::move(other.ip_)),
	host_(std::move(other.host_)),
	state_(other.state_),
	clients_(std::move(other.clients_)),
	pollFds_(std::move(other.pollFds_)),
	channels_(std::move(other.channels_))
{}

void Server::run() {
	listenSo_.initListener(cfg_.getPort());
	host_ = resolveHost(ip_ = fetchPublicFacingIP());
	pollFds_.push_back({listenSo_.getFd(), POLLIN, 0});

	state_ = IRC_RUNNING | IRC_ACCEPTING;

	std::cout << "Server starting on port " << cfg_.getPort() << " with " << pollFds_.size() << " fds" << std::endl;

	while (IRC_RUNNING & state_) {//check for FLUSH state_ such as server error messages to clients?
		try {
			if (poll(pollFds_.data(), pollFds_.size(), -1) < 0) {
				if (errno == EINVAL || errno == ENOMEM) {
					if (clients_.empty()) {
						state_ &= ~(IRC_ACCEPTING | IRC_RUNNING);//exit immediately
					}
					rmClient(pollFds_.back().fd);
					state_ &= ~IRC_ACCEPTING;
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
				state_ &= ~(IRC_ACCEPTING | IRC_RUNNING);//exit immediately
			}
			rmClient(pollFds_.back().fd);
			state_ &= ~IRC_ACCEPTING;
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
				if (IRC_ACCEPTING & state_) {
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
			state_ &= ~IRC_ACCEPTING; //stop accepting
		} else if (errno != EAGAIN && errno != EWOULDBLOCK) {
			std::cerr << "accept4() error: " << strerror(errno) << std::endl;
		}
		return;
	}

	int fd = clientSock.getFd();
	addClient(clientSock);

	std::cout << YELLOWIRC
			<< "Accepted new connection from " 
			<< clientSock.getIpStr() << ":"
			<< ntohs(clientSock.getAddr().sin_port) 
			<< " (FD: " << fd << ")" << RESETIRC << std::endl;

	clients_.at(fd).toSend(IrcMessages::passRequest());
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
		clients_.emplace(fd, Client(std::move(sock), &pollFds_.back()));
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

		if (IRC_ACCEPTING ^ state_) {
			state_ |= IRC_ACCEPTING; //start accepting again if the server was not accepting (due to maxing out)
		}

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
			#ifdef IRC_DEBUG_PRINTS
				cout << "isAuthenticated = false" << endl;
			#endif
			while ((pos = msgs.find("\r\n")) != std::string::npos) {
				line = msgs.substr(0, pos);
				if (processAuth(clients_.at(fromFd), msgs.substr(0, pos)) == false) {
					return false;
				}
				msgs.erase(0, pos + 2);
			}
		} else {
			#ifdef IRC_DEBUG_PRINTS
				int ms = 50;
				// cout << YELLOWIRC << "waiting " << ms << "ms, msg: " << msgs << RESETIRC << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(ms));
			#endif
			while ((pos = msgs.find("\r\n")) != std::string::npos) {
				line = msgs.substr(0, pos);
				if (line.find("QUIT") == 0) {
				#ifdef IRC_DEBUG_PRINTS
					std::cout << "QUIT from fd:" << fromFd << std::endl;
				#endif
					return false;
				}
				processCommand(fromFd, line);
				msgs.erase(0, pos + 2);
			}
		}
	} catch (std::exception& e) {
		std::cerr << "Exception caught in handleMsgs(): " << e.what() << "Client fd:" << fromFd << std::endl;
	}
	return true;
}

//if this returns false, client should be removed
bool	Server::processAuth(Client& newClient, std::string msg) {
	#ifdef IRC_AUTH_PRINTS
		cout << GREENIRC << "authenticate() msg:" << msg << RESETIRC << endl;
	#endif
	if (newClient.hasReceivedNick() == false) {
		size_t nickpos = msg.find("NICK ");
		if (nickpos != std::string::npos) {
			newClient.setNick(msg.substr(nickpos + 5));//do i need to skip spaces?
			newClient.setNickReceived();
		#ifdef IRC_AUTH_PRINTS
			std::cout << GREENIRC << "--nick:" << newClient.getNick() << RESETIRC << std::endl;
		#endif
			return true;
		}
	}

	if (newClient.hasReceivedUser() == false) {
		size_t userpos = msg.find("USER ");
		if (userpos != std::string::npos) {
			userpos += 5;
			newClient.setUser(msg.substr(userpos, msg.substr(userpos).find(' ')));//can user contain spaces?
			newClient.setUserReceived();
			#ifdef IRC_AUTH_PRINTS
				std::cout << GREENIRC << "--user:" << newClient.getUser() << RESETIRC << std::endl;
			#endif
			return true;
		}
	}

	size_t passpos = msg.find("PASS ");
	if (passpos != std::string::npos) {
		passpos += 5;
		passpos += (msg.substr(passpos).find_first_not_of(' ') != std::string::npos) ? msg.substr(passpos).find_first_not_of(' ') : 0;
		cout << passpos << endl;
		std::string password = msg.substr(passpos);
	#ifdef IRC_AUTH_PRINTS
		cout << "~~checking password~~" << endl;
	#endif
		if (cfg_.CheckPassword(password) == true) {
			newClient.setAuthenticated();
			newClient.toSend(IrcMessages::welcome(newClient.getNick(), cfg_.getServName()));
			return true;
		}
	}

	if (msg.find("PING") != std::string::npos) {
		newClient.toSend("PONG rrr");
		return true;
	}
	if (msg.find("CAP LS") != std::string::npos) {
		return true;
	}
	#ifdef IRC_AUTH_PRINTS
		cout << "pass attempt: " << newClient.getAuthAttempts() << endl;
	#endif
	newClient.addAuthAttempt();
	newClient.toSend(IrcMessages::wrongPass());
	if (newClient.getAuthAttempts() < cfg_.getMaxAuthAttempts()) {
		return true;
	}
	return false;
}


void	Server::gracefulShutdown() {
	#ifdef IRC_CLI_PRINT
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
	for (auto& cliFd : clients_) {
		cliFd.second.toSend(IrcMessages::errorQuit(cliFd.second.getNick()));
	}
	// state_ |= IRC_FLUSH;
	state_ &= ~(IRC_ACCEPTING | IRC_RUNNING);
}

void Server::checkRegistration(int fd) {
	if (!clients_[fd].getNick().empty() && !clients_[fd].getUser().empty() && !clients_[fd].isAuthenticated()) {
		clients_[fd].setAuthenticated();  // Assuming you want to set them as authenticated
		clients_.at(fd).toSend(IrcMessages::motd());
	}
}

std::string	Server::fetchPublicFacingIP() {
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

std::string	Server::resolveHost(std::string ip) {
	sockaddr_in sa{};
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &sa.sin_addr);

	char host[NI_MAXHOST];
	int err = getnameinfo((sockaddr*)&sa, sizeof(sa), host, sizeof(host), nullptr, 0, NI_NAMEREQD);
	if (err != 0) {
		std::cerr << "Reverse DNS failed: " + std::string(gai_strerror(err)) << " in resolveHost()" << std::endl;
		return "localhost";
	}
	return std::string(host);
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
