#include "../inc/Server.hpp"

Server::Server(Config&& cfg) : cfg_{std::move(cfg)}, listener_{} {}

void Server::ft_send(int fd, const std::string& message) {
	try {
		clients_.at(fd).appendToSendBuf(message);
	} catch (std::out_of_range& e) {
		std::cerr << "clients_ map access at nonexisting key:" << fd << " - " << e.what() << std::endl;
	}
}

void Server::sendWelcome(int fd) {
	std::string nick;
	auto clientIt = clients_.find(fd);
	if (clientIt != clients_.end()) {
		nick = clients_.at(fd).getNick();
	}
	std::string welcome = 
		":localhost 001 " + nick + " :Welcome to the Internet Relay Network\r\n" +
		":localhost 002 " + nick + " :Your host is localhost\r\n" +
		":localhost 003 " + nick + " :This server was created today\r\n" +
		":localhost 004 " + nick + " :localhost 1.0\r\n";
	ft_send(fd, welcome.c_str());
}

void Server::checkRegistration(int fd) {
	if (!clients_[fd].getNick().empty() && !clients_[fd].getUser().empty() && !clients_[fd].isAuthenticated()) {
		clients_[fd].setAuthenticated();  // Assuming you want to set them as authenticated
		sendWelcome(fd);
	}
}

void Server::run() {
	std::cout << "Starting server..." << std::endl;
	listener_.makeListener(cfg_.getPort());// Socket wrapper to bind+listen+non-blocking

	pollFds_.clear();
	pollFds_.push_back({listener_.getFd(), POLLIN, 0});
	std::cout << "Server setup complete on port " << cfg_.getPort() << std::endl;//add IP address
	mainLoop();
}

void Server::mainLoop() {
	std::cout << "Entering main loop with " << pollFds_.size() << " file descriptors" << std::endl;
	
	while (true) {
		int ready = poll(pollFds_.data(), pollFds_.size(), -1);
		if (ready < 0) {
			std::cerr << "poll() error: " << strerror(errno) << std::endl;
			if (errno == EINTR) continue;
			throw std::runtime_error("poll() failed");
		}
		else if (ready == 0) {
			std::cerr << "poll() timeout (shouldn't happen with infinite timeout)" << std::endl;
			continue;
		}

		int fd = 0;
		for (unsigned long i = pollFds_.size(); i-- > 0;) {
			fd = pollFds_.at(i).fd;

			if (pollFds_[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
				std::cerr << "Error condition on fd " << fd << std::endl;
				rmClient(i, fd);
				continue;
			}
			if (pollFds_[i].revents & POLLIN) {
				if (fd == listener_.getFd()) {
					acceptNewConnection();
				} else {
					if (clients_.at(fd).receiveAndProcess(this) == false) {
						rmClient(i, fd);
						continue;
					}
				}
			}
			if (pollFds_[i].revents & POLLOUT) {
				if (clients_.at(fd).sendFromBuf() == false) {
					rmClient(i, fd);
				}
			}
		}
	}
}

void Server::acceptNewConnection() {
	Socket	clientSock;
	int		retries = 0;

	while (listener_.accept(clientSock) == false) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			return;
		} else if (retries++ == maxRetries_) {
			std::cerr << "Accept4 failed:" << strerror(errno) << "for max " << maxRetries_ << " times." << std::endl;
			return;
		} else {//EINTR and any transient or permanent error -> we log and retry up to maxRetries_ times
			std::cerr << "Accept4 failed:" << strerror(errno) << std::endl;
		}
	}

	std::cout << "Accepted new connection from " 
			  << clientSock.getIpStr() << ":"
			  << ntohs(clientSock.getAddr().sin_port) 
			  << " (FD: " << clientSock.getFd() << ")" << std::endl;

	addClient(clientSock);
}

//removes Client from its own joinedChannels Channel objects, server's pollFds_ vector, and server's clients_ map
void Server::rmClient(unsigned int rmPollfdIndex, int rmFd) {
	for (const auto& [channelName, _] : clients_.at(rmFd).getJoinedChannels()) { // Iterate over joined channel names
		auto channelIt = channels_.find(channelName); // Find the Channel in the map

		if (channelIt != channels_.end()) {
			channelIt->second.removeClient(rmFd); // Call removeClient on the Channel object
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
}

//constructs Client with the given socket and adds its fd to pollFds_ and the object itself to clients_ map
void Server::addClient(Socket& sock) {
	int fd = sock.getFd();
	try {
		pollFds_.push_back({sock.getFd(), POLLIN | POLLOUT, 0});
	} catch (std::exception& e) {
		std::cerr << "addClient to pollFds_ (fd: " << fd << ") failed: " << e.what() << std::endl;
		return ;
	}
	try {
		clients_.emplace(fd, Client(std::move(sock)));	
	} catch (std::exception& e) {
		std::cerr << "addClient to map (fd: " << fd << ") failed: " << e.what() << std::endl;
		rmClient(pollFds_.size() - 1, fd);
		return;
	}

	// Send welcome message
	std::string welcome = "Welcome to " + cfg_.getServName() + "!\nPlease register with NICK and USER\r\n";
	ft_send(fd, welcome.c_str());

	// Send initial MOTD (makes irssi happy)
	std::string motd = 
		":localhost 375 * :- Message of the Day -\r\n"
		":localhost 376 * :Another day another slay\r\n";
	ft_send(fd, motd.c_str());
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

