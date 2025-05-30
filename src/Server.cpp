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
	state_(other.state_),
	clients_(std::move(other.clients_)),
	pollFds_(std::move(other.pollFds_)),
	channels_(std::move(other.channels_)) {}

void Server::run() {
	listenSo_.initListener(cfg_.getPort());
	pollFds_.push_back({listenSo_.getFd(), POLLIN, 0});

	state_ = IRC_RUNNING | IRC_ACCEPTING;

	std::cout << "Server starting on port " << cfg_.getPort() << " with " << pollFds_.size() << " fds" << std::endl;

	while (IRC_RUNNING & state_) {
		try {
			unsigned long	pollSize = pollFds_.size();
			if (poll(pollFds_.data(), pollSize, -1) < 0) {
				if (errno == EINVAL || errno == ENOMEM) {
					rmClient(pollFds_.back().fd);
					state_ &= ~IRC_ACCEPTING;
				}
				std::cerr << "poll() returned -1 with errno: " << strerror(errno) << std::endl;
				continue;
			}
			#ifdef IRC_DEBUG_PRINTS
				std::cout << "We poll" << std::endl;
			#endif
			handleEvents();
			checkInactivity();
			if (pollFds_.size() != pollSize) {
				updatePollfds();
			}
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
	removes Client from all of its own joinedChannels (and destroys all channels where that client was the last remaining),
	server's pollFds_ vector, and server's clients_ map
*/
void Server::rmClient(int rmFd) {
	try {
		for (int i = pollFds_.size() - 1; i >= 0; --i) {
			if (pollFds_.at(i).fd == rmFd) { pollFds_.erase(pollFds_.begin() + i); }
		}

		for (const auto& [channelName, _] : clients_.at(rmFd).getJoinedChannels()) {
			auto channelIt = channels_.find(channelName);

			if (channelIt != channels_.end()) {
				channelIt->second.removeClient(rmFd);
				if (channelIt->second.isEmpty()) {
					channels_.erase(channelName);
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
				processCommand(fromFd, line);//consider having processCommand return bool false when QUIT is typed, so we know in poll loop to rmClient
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
	state_ &= ~(IRC_ACCEPTING | IRC_RUNNING);
}

void	Server::updatePollfds() {
	for (auto& pair : clients_) {
		for (int i = pollFds_.size() - 1; i >= 0; i--) {
			if (pair.first == pollFds_.at(i).fd) {
				pair.second.setPfdPtr(&pollFds_.at(i));
			}
		}
	}
}

void	Server::checkInactivity() {
	std::vector<int>	inactiveFds;

	for (auto& pair : clients_) {
		if (pair.second.isInactive(cfg_.getAllowedInactivity())) {
			inactiveFds.push_back(pair.first);
		}
	}

	for (int i = inactiveFds.size() - 1; i >= 0; i--) {
		rmClient(inactiveFds[i]);
	}
}

void Server::checkRegistration(int fd) {
	if (!clients_[fd].getNick().empty() && !clients_[fd].getUser().empty() && !clients_[fd].isAuthenticated()) {
		clients_[fd].setAuthenticated();  // Assuming you want to set them as authenticated
		clients_.at(fd).toSend(IrcMessages::motd());
	}
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
