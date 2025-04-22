
#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "Socket.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <string_view>
#include <netinet/in.h>
#include <system_error>
#include <sys/socket.h> //SOMAXCONN, listen()
#include <cassert>
#include <unistd.h>
// #include <fcntl.h>

class Config {
	const std::string	listenPort_;
	const std::string	password_;
	const std::string	serverName_ = "ircserv wb";

public:
	Config();
	Config(std::string& listenPort, std::string& passw);
	Config(Config&)	= default;
	~Config()		= default;

	void		validate();
	int			getPort() const& noexcept {return std::stoi(listenPort_);}
	std::string	getPassw() const& noexcept {return password_;}
	std::string	getPassw() const& noexcept {return serverName_;}
};

#endif
