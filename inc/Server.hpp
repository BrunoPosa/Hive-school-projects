#pragma once

extern short g_state;

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
#include "Socket.hpp"
#include "Config.hpp"

enum IRCState : short {
    IRC_RUNNING   = 0x1,
    IRC_ACCEPTING = 0x2
};

#define REDIRC "\033[1;31m"
#define YELLOWIRC "\033[33m"
#define GREENIRC "\033[1;32m"
#define RESETIRC "\033[0m"

class Server {
private:
	Config	cfg_;
	Socket	listener_;
	std::vector<struct pollfd>	pollFds_;
	std::map<int, Client>	clients_;
	std::map<std::string, Channel>	channels_;
	int defaultUserCount_ = 0;

	void	ft_send(int fd, const std::string& message);
	void	handleAllEvents();
	void	acceptNewConnection();
	void	addClient(Socket& sock);
	void	rmClient(unsigned int rmPollfdIndex, int rmFd);
	void	checkRegistration(int fd);
	void	sendWelcome(Client& client);
	void	splitAndProcess(int fromFd);
	void	processCommand(int fd, const std::string& message);

	void	cmdNick(int fd, const std::string& message);
	void	cmdUser(int fd, const std::string& message);
	void	cmdJoin(int fd, const std::string& message);
	void	cmdPrivMsg(int fd, const std::string& message);
	void	cmdPing(int fd, const std::string& message);
	void	cmdTopic(int fd, const std::string& message);
	void	cmdMode(int fd, const std::string& message);
	void	cmdKick(int sender_fd, const std::vector<std::string>& params);
	void	kickUser(int sender_fd, const std::string& channelName, const std::string& reason, const std::string& targetNick); // Kick user from channel
	
public:
	Server()	= default;
	explicit	Server(Config&& cfg);
	~Server()	= default;

	int	getPort() const noexcept {return cfg_.getPort();}
	int	getServerFd() const { return listener_.getFd(); }
	int	getClientFdByNick(const std::string& nick) const;
	std::string	getNickByFd(int fd) const;
	void	run();
};
