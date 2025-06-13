#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <unistd.h>
#include <string>
#include <cstring>//strerror
#include <iostream>
#include <limits.h>//hostnamemax
#include <fcntl.h>
#include <arpa/inet.h> //inet_ntop
#include <netinet/in.h>//sockaddr_in
#include <sys/socket.h> //SOMAXCONN, listen()...

/**
 * @brief RAII wrapper for a non‑blocking TCP/IPv4 socket.
 *
 * On construction, creates a socket and sets it non‑blocking.
 * Closes on destruction.
 * Throws on failures.
 */
 class Socket {
	int			fd_;
	sockaddr_in	addr_;
	std::string	host_;
	bool		isListening_;
	bool		setNonBlocking(int fd) const;

public:
	Socket();
	explicit Socket(int fd, sockaddr_in addr);
	Socket(const Socket& other)				= delete;
	Socket& operator=(const Socket& other)	= delete;
	Socket(Socket&& other) noexcept;
	Socket& operator=(Socket&& other) noexcept;
	~Socket() noexcept;

	void	initListener(uint16_t port);
	bool	accept(Socket& toSocket) const;
	std::string	resolveHost();

	int			getFd() const noexcept {return fd_;}
	sockaddr_in getAddr() const noexcept {return addr_;}
	std::string	getIpStr() const;
	uint16_t	getPortNum() const { return ntohs(addr_.sin_port); }
	bool		isListener() const noexcept {return isListening_;}
};

#endif
