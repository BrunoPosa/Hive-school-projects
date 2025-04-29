#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <string>
#include <string_view>
#include <iostream>
#include <netinet/in.h>
#include <system_error>
#include <sys/socket.h> //SOMAXCONN, listen()
#include <cassert>

/**
 * @brief RAII wrapper for a non‑blocking TCP/IPv4 socket.
 *
 * On construction, creates a socket and sets it non‑blocking.
 * Closes on destruction.
 * Throws on failure.
 */

class Socket {
	int			fd_;
	sockaddr_in	addr_;
	bool		isListening_;

public:
	Socket();
	explicit Socket(int fd, sockaddr_in addr, bool isListener) noexcept;
	Socket(const Socket& other)				= delete;
	Socket& operator=(const Socket& other)	= delete;
	Socket(Socket&& other) noexcept;
	Socket& operator=(Socket&& other) noexcept;
	~Socket();

	void	makeListener(uint16_t port);
	Socket	accept() const;
	ssize_t	send(std::string_view data) const;
	ssize_t	receive(std::string& buf) const;

	int			getFd() const noexcept {return fd_;}
	sockaddr_in getAddr() const {return addr_;}
	bool		isListener() const noexcept {return isListening_;}
};

#endif
