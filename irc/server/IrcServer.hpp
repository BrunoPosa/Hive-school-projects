/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:58:11 by bposa             #+#    #+#             */
/*   Updated: 2025/04/22 20:20:12 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

#define IRC_BUFSIZE 4096
#define REDIRC "\033[1;31m"
#define YELLOWIRC "\033[33m"
#define GREENIRC "\033[1;32m"
#define RESETCOLORIRC "\033[0m"

#include "Config.hpp"
#include "Socket.hpp"
#include "Connection.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <poll.h>

class IrcServ {
	Config					config_;
	int						listenFd_;
	std::vector<pollfd>		pollFds_;
	std::vector<Connection>	connections_;
	Command					commands_;
	std::unordered_map<std::string, Channel> channels_;

public:
	IrcServ(Config cnfg);
	~IrcServ();
	IrcServ()	= delete;
	IrcServ(IrcServ&)	= delete;
	IrcServ&	operator=(IrcServ&) = delete;
};

#endif
