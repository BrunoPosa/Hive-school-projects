
#ifndef CONNECTION_HPP
# define CONNECTION_HPP

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

class Connection {
	Socket		sock_;
	std::string	nick_;
	std::string	user_;
	bool		registered_;

public:
	Connection();
	Connection(Connection&);
	~Connection();

};

#endif
