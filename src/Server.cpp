#include "../inc/irc.hpp"

// Default constructor
Server::Server() : port_(0), password_(""), serverFd_{} {
	// Initialize default values
}
// Parameterized constructor
Server::Server(const int port, const std::string& password) : port_(port), password_(password), serverFd_{} {
	// Initialize with provided values
}
// Destructor
Server::~Server() {
	// Cleanup resources if needed
}

void Server::sendWelcome(int fd) {
	const std::string& nick = clients_[fd].getNick();
	std::string welcome = 
		":localhost 001 " + nick + " :Welcome to the Internet Relay Network\r\n" +
		":localhost 002 " + nick + " :Your host is localhost\r\n" +
		":localhost 003 " + nick + " :This server was created today\r\n" +
		":localhost 004 " + nick + " :localhost 1.0\r\n";
	// send(fd, welcome.c_str(), welcome.size(), 0);
	sockets_[fd].send(welcome);
}

void Server::checkRegistration(int fd) {
	Client& client = clients_[fd];
	if (!client.getNick().empty() && !client.getUser().empty() && !client.isAuthenticated()) {
        client.setAuthenticated();  // Assuming you want to set them as authenticated
        sendWelcome(fd);
	}
}

void Server::run() {
	std::cout << "Starting server..." << std::endl; // Debug output
	setupServer(); // Set up the server
	mainLoop(); // Start the main loop
}
void Server::setupServer() {
    serverFd_.makeListener(port_);// Socket wrapper to bind+listen+non-blocking
	// Initialize pollFds_ with server socket
	pollFds_.clear();
	pollFds_.push_back((pollfd){serverFd_.getFd(), POLLIN, 0});
	std::cout << "Server setup complete on port " << port_ << std::endl;
}
void Server::mainLoop() {
	std::cout << "Entering main loop with " << pollFds_.size() << " file descriptors" << std::endl;
	
	while (true) {
		
		int ready = poll(&pollFds_[0], pollFds_.size(), -1);
		if (ready < 0) {
			std::cerr << "poll() error: " << strerror(errno) << std::endl;
			if (errno == EINTR) continue;
			throw std::runtime_error("poll() failed");
		}
		else if (ready == 0) {
			std::cout << "poll() timeout (shouldn't happen with infinite timeout)" << std::endl;
			continue;
		}
		
		// Check all file descriptors, not just server socket
		for (size_t i = 0; i < pollFds_.size(); i++) {
			if (pollFds_[i].revents & POLLIN) {
				if (pollFds_.at(i).fd == serverFd_.getFd()) { // Server socket
					acceptNewConnection();
				}
				else { // Client socket
					handleClient(i);
				}
			}
			if (pollFds_[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
				std::cerr << "Error condition on fd " << pollFds_[i].fd << std::endl;
				pollFds_.erase(pollFds_.begin() + i);
				sockets_.erase(pollFds_.at(i).fd);
				i--; // Adjust index after erase
			}
		}
	}
}
void Server::acceptNewConnection() {
	Socket	clientSock = serverFd_.accept();
	int		clientFd   = clientSock.getFd();

	std::cout << "Accepted new connection from " 
			  << inet_ntoa(clientSock.getAddr().sin_addr) << ":"
			  << ntohs(clientSock.getAddr().sin_port) 
			  << " (FD: " << clientFd << ")" << std::endl;

	pollFds_.push_back((pollfd){clientFd, POLLIN | POLLOUT, 0});
	sockets_.emplace(clientFd, std::move(clientSock));

	// Send welcome message
	std::string welcome = "Welcome to ft_irc!\nPlease register with NICK and USER\r\n";
	if (send(clientFd, welcome.c_str(), welcome.size(), 0) < 0) {
		std::cerr << "send() error: " << strerror(errno) << std::endl;
	}
	// Initialize new client
	clients_[clientFd] = Client();  // Sets registered=false by default
	
	// Send initial MOTD (makes irssi happy)
	std::string motd = 
		":localhost 375 * :- Message of the Day -\r\n"
		":localhost 376 * :Another day another slay\r\n";
	send(clientFd, motd.c_str(), motd.size(), 0);
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
