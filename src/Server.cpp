#include "../inc/Server.hpp"

using std::cout;
using std::endl;
using std::string;

short	g_state = 0;

Server::Server(Config&& cfg) : cfg_{std::move(cfg)}, listenSo_{} {}

void Server::run() {
	listenSo_.make();
	listenSo_.listen(cfg_.getPort());
	pollFds_.push_back({listenSo_.getFd(), POLLIN, 0});

	g_state = IRC_RUNNING | IRC_ACCEPTING;

	std::cout << "Server starting on port " << cfg_.getPort()
		<< " with " << pollFds_.size() << " fds" << std::endl;//add IP address

	while (IRC_RUNNING & g_state) {
		if (poll(pollFds_.data(), pollFds_.size(), -1) < 0) {
			if (errno == EINVAL || errno == ENOMEM) {
				g_state &= ~IRC_ACCEPTING;
			}
			std::cerr << "poll() -1 with: " << strerror(errno) << std::endl;
			continue;
		}
		handleAllEvents();
	}
}

void Server::handleAllEvents() {
	pollfd	pfd = {};

	for (int i = pollFds_.size(); i-- > 0;) {
		pfd = pollFds_.at(i);

		if (POLLIN & pfd.revents) {
			if (pfd.fd == listenSo_.getFd()) {
				if (IRC_ACCEPTING & g_state) { acceptNewConnection(); }
			} else {
				if (clients_.at(pfd.fd).receive() == false) {
					rmClient(i, pfd.fd);
					continue;
				}
				splitAndProcess(pfd.fd);
			}
		}
		if ((POLLERR | POLLHUP | POLLNVAL) & pfd.revents) {
			std::cerr << "revents error: " << pfd.revents << " on fd " << pfd.fd << std::endl;
			rmClient(i, pfd.fd);
		} else if (POLLOUT & pfd.revents) {
			if (clients_.at(pfd.fd).send() == false) {
				rmClient(i, pfd.fd);
			}
		}
	}
}

void Server::acceptNewConnection() {
	Socket	clientSock;

	if (listenSo_.accept(clientSock) == false) {
		if (errno == EMFILE || errno == ENFILE || errno == ENOMEM || errno == ENOBUFS) {
			g_state &= ~IRC_ACCEPTING; //stop accepting
		} else if (errno != EAGAIN && errno != EWOULDBLOCK) {
			std::cerr << "accept4() error: " << strerror(errno) << std::endl;
		}
		return;
	}

	std::cout << YELLOWIRC
			<< "Accepted new connection from " 
			<< clientSock.getIpStr() << ":"
			<< ntohs(clientSock.getAddr().sin_port) 
			<< " (FD: " << clientSock.getFd() << ")" << RESETIRC << std::endl;

	int fd = clientSock.getFd();
	addClient(clientSock);

	try {
		clients_.at(fd).toSend(
			"Welcome to "
			+ cfg_.getServName()
			+ "!\nPlease register with NICK and USER\r\n"
			":localhost 375 * :- Message of the Day -\r\n"
			":localhost 376 * :Another day another slay\r\n");

	} catch (std::exception& e) {
		std::cerr << "acceptNewConnection() with fd: " << fd << " : " << e.what() << std::endl;
	}
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
		rmClient(pollFds_.size() - 1, fd);
		return;
	}
}

//removes Client from its own joinedChannels Channel objects, server's pollFds_ vector, and server's clients_ map
void Server::rmClient(unsigned int rmPollfdIndex, int rmFd) {
	try {
		for (const auto& [channelName, _] : clients_.at(rmFd).getJoinedChannels()) {
			auto channelIt = channels_.find(channelName);

			if (channelIt != channels_.end()) {
				channelIt->second.removeClient(rmFd);
			}
		}

		if (rmPollfdIndex > 0 && rmPollfdIndex < pollFds_.size()) {
			pollFds_.erase(pollFds_.begin() + rmPollfdIndex);
		} else {
			std::cerr << "could not rmClient pollfdIndex:" << rmPollfdIndex << std::endl;
		}

		auto clientIt = clients_.find(rmFd);
		if (clientIt != clients_.end()) {
			clients_.erase(clientIt);
		} else {
			std::cerr << "could not rmClient from map at fd:" << rmFd << std::endl;
		}

		if (IRC_ACCEPTING ^ g_state) {
			g_state |= IRC_ACCEPTING; //raise back accepting flag if it was down
		}
	} catch (std::exception& e) {
		std::cerr << "rmClient (fd: " << rmFd << ") failed: " << e.what() << std::endl;
	}
}

void	Server::splitAndProcess(int fromFd) {
	try {
		size_t pos = 0;
		std::string line;
		std::string	msgs = clients_.at(fromFd).getMsgs();

		while ((pos = msgs.find("\r\n")) != std::string::npos) {
			line = msgs.substr(0, pos);
			processCommand(fromFd, line);
			msgs.erase(0, pos + 2);
		}
	} catch (std::bad_alloc& e) {
		std::cerr << "Error during splitAndProcess(): " << e.what() << "Client fd:" << fromFd << std::endl;
	}
}

void Server::sendWelcome(Client& client) {
	try {
		std::string nick = client.getNick();

		client.toSend(
			":localhost 001 " + nick + " :Welcome to the Internet Relay Network\r\n"
			":localhost 002 " + nick + " :Your host is localhost\r\n"
			":localhost 003 " + nick + " :This server was created today\r\n"
			":localhost 004 " + nick + " :localhost 1.0\r\n");
	} catch (std::bad_alloc& e) {
		std::cerr << "sendWelcome() failed: " << e.what() << std::endl;
	}
}

void Server::checkRegistration(int fd) {
	if (!clients_[fd].getNick().empty() && !clients_[fd].getUser().empty() && !clients_[fd].isAuthenticated()) {
		clients_[fd].setAuthenticated();  // Assuming you want to set them as authenticated
		sendWelcome(clients_.at(fd));
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
