#pragma once


// System
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <cerrno>
#include <cstring>

// Standard Template Library
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <cctype>

// Project Headers
#include "error.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server {
public:
	Server();// Default constructor
	Server(const int port, const std::string& password);    // Parameterized constructor
	~Server();

	// setters
	void setPort(const int port) { port_ = port; }
	void setPassword(const std::string& password) { password_ = password; }
	// void setServerFd(int fd) { serverFd_ = fd; } // TODO change this to work with Socket
	// getters
	const std::string& getPassword() const { return password_; }

	int getPort() const { return port_; }
	int getServerFd() const { return serverFd_; }
	int getClientFdByNick(const std::string& nick) const;
	std::string getNickByFd(int fd) const;

	void run(); // Start the server
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
	void cmdPing(int fd, const std::string& message);       // Handle PING command
	void cmdTopic(int fd, const std::string& message);     // Handle TOPIC command
	void cmdMode(int fd, const std::string& message);
	void cmdKick(int sender_fd, const std::vector<std::string>& params);      // Handle KICK command
	
	void kickUser(int sender_fd, const std::string& channelName, const std::string& reason, const std::string& targetNick); // Kick user from channel

	int port_;
	std::string password_;

    Socket               serverFd_; // socket wrapper for serverFd_
    std::map<int, Socket> sockets_; // per-client socket objects

	// std::vector<int> clientFds_;                            // Vector of client file descriptors
	std::vector<struct pollfd> pollFds_;                    // Vector of poll file descriptors for clients
	std::map<int, Client> clients_;                         // Map of client file descriptors to Client objects
	int defaultUserCount_ = 0;                              // Default user count for the server
	std::map<std::string, Channel> channels_;               // Map of channel names to Channel objects
};
	
	int argCheck(int argc, char* argv[], Server& server); // Take Server reference as parameter
	bool isValidPort(const std::string& port);
	bool isValidPassword(const std::string& password);
