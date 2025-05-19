#include "../inc/Server.hpp"

using std::cout;
using std::endl;
using std::string;

Server	*g_servPtr = nullptr;

Server::Server(Config&& cfg) : cfg_{std::move(cfg)}, listenSo_{} {}

void Server::run() {
	listenSo_.initListener(cfg_.getPort());
	pollFds_.push_back({listenSo_.getFd(), POLLIN, 0});

	state = IRC_RUNNING | IRC_ACCEPTING;

	std::cout << "Server starting on port " << cfg_.getPort()
		<< " with " << pollFds_.size() << " fds" << std::endl;//add IP address

	while (IRC_RUNNING & state) {
		try {
			if (poll(pollFds_.data(), pollFds_.size(), -1) < 0) {
				if (errno == EINVAL || errno == ENOMEM) {
					state &= ~IRC_ACCEPTING;
				}
				std::cerr << "poll() returned -1 with errno: " << strerror(errno) << std::endl;
				continue;
			}
			handleEvents();
		} catch (const std::exception& e) {
			std::cerr << "Exception caught inside poll loop: " << e.what() << std::endl;
		}
	}
}

/*
	question the requirement of all 3 ifs not being in an if-else block
	(bc when adding/removing a client during first if block, index and map needs updating)
	not a huge deal, but ugly and cumbersome. 
	Assumption is for 1st if being separate is that POLLIN and POLLERR/HUP/NVAL are NOT mutually exclusive, so we should still process input on error
	-Test: make server recv buffer 1byte and then wait 1s, in the meantime disconnect from the client, and see if the serv receives the full message
	then i'll know for sure if kernel buf keeps its huge buffer after a client disconnects
	-ToDo: timeout if no activity from client bc monopolyizing the resourses
*/
void Server::handleEvents() {
	for (int i = pollFds_.size() - 1; i >= 0; --i) {
		pollfd&	pfd = pollFds_[i];

		if (POLLIN & pfd.revents) {
			if (pfd.fd == listenSo_.getFd()) {
				if (IRC_ACCEPTING & state) {
					acceptNewConnection();
					continue;
				}
			} else {
				if (clients_.at(pfd.fd).receive() == false || handleMsgs(pfd.fd) == false) {
					rmClient(pfd.fd);
					continue;
				}
			}
		}
		if ((POLLERR | POLLHUP | POLLNVAL) & pfd.revents) {
			std::cerr << "revents error: " << pfd.revents << " on fd " << pfd.fd << std::endl;
			rmClient(pfd.fd);
		} else if (POLLOUT & pfd.revents) {
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
			state &= ~IRC_ACCEPTING; //stop accepting
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
		pollFds_.push_back({sock.getFd(), POLLIN | POLLOUT, 0});
	} catch (std::exception& e) {
		std::cerr << "addClient to pollFds_ (fd: " << fd << ") failed: " << e.what() << std::endl;
		return;
	}
	try {
		clients_.emplace(fd, Client(std::move(sock)));	
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

		if (IRC_ACCEPTING ^ state) {
			state |= IRC_ACCEPTING; //start accepting again if the server was not accepting (due to maxing out)
		}
	} catch (std::exception& e) {
		std::cerr << "Exception caught in rmClient(): " << e.what() << " fd: " << rmFd << std::endl;
	}
}

bool	Server::handleMsgs(int fromFd) {
	try {
		size_t pos = 0;
		std::string line;
		std::string	msgs = clients_.at(fromFd).getMsgs();

		// if (clients_.at(fromFd).isAuthenticated() == false) {
		// 	if (authenticate(clients_.at(fromFd), msgs) == false) {
		// 		return false;
		// 	}
		// } else {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			while ((pos = msgs.find("\r\n")) != std::string::npos) {
				line = msgs.substr(0, pos);
				processCommand(fromFd, line);//consider having processCommand return bool false when QUIT is typed, so we know in poll loop to rmClient
				msgs.erase(0, pos + 2);
			}
		// }
	} catch (std::exception& e) {
		std::cerr << "Exception caught in splitAndProcess(): " << e.what() << "Client fd:" << fromFd << std::endl;
	}
	return true;
}

//if authenticate returns false, client should be removed
bool	Server::authenticate(Client& newClient, std::string& msg) {
	size_t pos = msg.find("\r\n");
	cout << YELLOWIRC << msg << RESETIRC << endl;
	if (pos != std::string::npos) {
		cout << msg << endl;
		if (msg.length() >= 6 && msg.find("CAP LS") == 0) {
			return true;
		} else if (msg.length() >= 4 && msg.find("PING") == 0) {
			return true;
		}
		if (msg.length() > 5 && msg.find("PASS ") == 0) {
			//skip spaces, as per rfc
			std::string password = msg.substr(5, pos - 5);

			if (cfg_.CheckPassword(password) == true) {
				newClient.setAuthenticated();
				newClient.toSend(IrcMessages::welcome(newClient.getNick(), cfg_.getServName()));
				return true;
			} else {
				newClient.toSend(IrcMessages::wrongPass());
			}
		}
		newClient.toSend(IrcMessages::wrongPass());
		return false;
	}
	return true;
}

void	Server::gracefulShutdown() {
	for (auto& cliFd : clients_) {
		cliFd.second.toSend(IrcMessages::errorQuit(cliFd.second.getNick()));
	}
	state &= ~(IRC_ACCEPTING | IRC_RUNNING);
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
