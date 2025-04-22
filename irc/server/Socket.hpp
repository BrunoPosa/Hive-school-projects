
#ifndef SOCKET_HPP
# define SOCKET_HPP

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

class Socket {
	int			fd_;
	sockaddr_in	addr_;
	bool		isListening_;

public:
	Socket();
	explicit Socket(int fd, bool isListener) noexcept;
	~Socket();

	void	makeListener(uint16_t port);
	Socket	accept() const;
	ssize_t	send(std::string_view data) const;
	ssize_t	receive(std::string& buf) const;

	int		getFd() const noexcept {return fd_;}
};

#endif
