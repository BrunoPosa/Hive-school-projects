#pragma once

// System
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <cerrno>
#include <cstring>
#include <csignal>

// System
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <cerrno>
#include <limits.h>//hostnamemax
#include <netdb.h>//gethostname

// Standard Template Library
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <cctype>

// Project Headers
#include "error.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Socket.hpp"
#include "Config.hpp"

//testing
#include <thread>
#include <fcntl.h>

class Server;
extern Server	*g_servPtr;

typedef struct cmdFunctionParameters {
	std::string					fullMsg;
	std::vector<std::string>	cmdParams;
} t_data;

#define REDIRC "\033[1;31m"
#define YELLOWIRC "\033[33m"
#define GREENIRC "\033[1;32m"
#define RESETIRC "\033[0m"

#define MAX_CLIENTS 999

// #define IRC_ON_SHUTDOWN_PRINT
// #define IRC_DEBUG_PRINTS
// #define IRC_POLL_PRINTS
#define IRC_AUTH_PRINTS
#define CMD_CONCAT_TEST_IRC //for evals

class Server {
private:
	Config	cfg_;
	Socket	listenSo_;
	std::string	ip_;
	std::string	host_;
	std::string	ircMsgDelimiter_;
	bool	accepting_;
	volatile sig_atomic_t	running_;
	std::map<int, Client>	clients_;
	std::vector<struct pollfd>	pollFds_;
	std::map<std::string, Channel>	channels_;
	std::unordered_map<std::string, std::function<void(int, const t_data&)>> cmds_;
	int defaultUserCount_ = 0;

	void	handleEvents();
	void	acceptNewConnection();
	void	addClient(Socket& sock);
	void	rmClient(int rmFd);
	bool	handleMsgs(int fromFd);
	bool	processAuth(int fromFd, std::string msg);
	void	dispatchCommand(int fd, const std::string& message);

	std::vector<std::string>	tokenize(std::istringstream& cmdParams);
	void		checkRegistration(int fd);
	void		ft_send(int fd, const std::string& message);

	void cmdNick(int fd, const t_data data);
	void cmdUser(int fd, const t_data data);
	void cmdJoin(int fd, const t_data data);
	void cmdPrivMsg(int fd, const t_data data);
	void cmdPing(int fd, const t_data data);
	void cmdTopic(int fd, const t_data data);
	void cmdMode(int fd, const t_data data);
	void cmdKick(int sender_fd, t_data data);
	void cmdInvite(int sender_fd, t_data data);
	void cmdPart(int fd, const t_data data);

	void kickUser(int sender_fd, const std::string& channelName, const std::string& reason, const std::string& targetNick); // Kick user from channel

public:
	Server();
	explicit	Server(Config&& cfg);
	Server(Server& other) = delete;
	Server(Server&& other);
	~Server()	= default;

	void	run();
	void	gracefulShutdown();
	int		getPort() const noexcept {return cfg_.getPort();}
	int		getServerFd() const { return listenSo_.getFd(); }
	int		getClientFdByNick(const std::string& nick) const;
	std::string	getNickByFd(int fd) const;
};
