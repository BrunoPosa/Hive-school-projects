#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>
#include <stdexcept>
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> 
#include <unistd.h> // For close function
#include <cstring> 
#include <cerrno> 
#include <stdexcept> // For std::runtime_error
#include <poll.h>
#include <arpa/inet.h> // For inet_ntop
#include <sstream> // For std::cerr
#include <fcntl.h> // For fcntl
#include <unordered_map> // For std::unordered_map


#include "error.hpp"

class Channel {
	private:
		std::string name;
		std::set<int> clients; // set of client file descriptors
	
	public:
		Channel() : name("default") {}
		Channel(const std::string& name) : name(name) {}
	
		void addClient(int fd) {
			clients.insert(fd);
			std::cout << "Added FD " << fd << " to channel " << name << "\n";
		}
	
		bool hasClient(int fd) const {
			return clients.find(fd) != clients.end();
		}
	
		void broadcast(int senderFd, const std::string& msg, const std::string& senderNick, int exceptFd = -1) {
			(void) senderFd; // Unused in this context
			std::string fullMsg = ":" + senderNick + " PRIVMSG " + name + " :" + msg + "\r\n";
			for (std::set<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
				if (*it != exceptFd) {
					send(*it, fullMsg.c_str(), fullMsg.length(), 0);
				}
			}
		}
	};

class Server {
public:
	// setters
	void setPort(const int port) { port_ = port; }
	void setPassword(const std::string& password) { password_ = password; }
	void setServerFd(int fd) { serverFd_ = fd; }
	// getters
	int getPort() const { return port_; }
	const std::string& getPassword() const { return password_; }
	int getServerFd() const { return serverFd_; }
	void run(); // Start the server
	Server();// Default constructor
	Server(const int port, const std::string& password);    // Parameterized constructor
	~Server();
private:
	void setupServer();                                     // Set up the server
	void mainLoop();                                        // Main loop for handling connections
	void acceptNewConnection();                             // Accept new connections
	void handleClient(size_t index);                        // Handle client communication
	void checkRegistration(int fd);                         // Check if client is registered
	void sendWelcome(int fd);                               // Send welcome message to client
	void handleClientError(int errorCode, size_t index);    // Handle client errors
	void processCommand(int fd, const std::string& message);// Process incoming commands
	void cmdNick(int fd, const std::string& message);       // Handle NICK command
	void cmdUser(int fd, const std::string& message);       // Handle USER command
	void cmdJoin(int fd, const std::string& message);       // Handle JOIN command
	void cmdPrivMsg(int fd, const std::string& message);    // Handle PRIVMSG command

	int port_;
	std::string password_;
	int serverFd_;
	std::vector<int> clientFds_;                            // Vector of client file descriptors
	std::vector<struct pollfd> pollFds_;                    // Vector of poll file descriptors for clients
	struct Client {
		std::string nick;
		std::string user;
		bool registered;
		bool nameChanged;

		std::set<std::string> joinedChannels; // Set of channels the client has joined
		void joinChannel(const std::string& channel) {
			joinedChannels.insert(channel);
		}
	};
	std::map<int, Client> clients_;                         // Map of client file descriptors to Client objects
	int defaultUserCount_ = 0;                              // Default user count for the server
	std::map<std::string, Channel> channels_;               // Map of channel names to Channel objects
};
	
	int argCheck(int argc, char* argv[], Server& server); // Take Server reference as parameter
	bool isValidPort(const std::string& port);
	bool isValidPassword(const std::string& password);
