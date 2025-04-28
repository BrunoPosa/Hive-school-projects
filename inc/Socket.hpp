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
public:
	Socket(); // create non-blocking socket
	explicit Socket(int fd, sockaddr_in addr, bool isListener) noexcept;
	~Socket();
	Socket(const Socket&)				= delete;
	Socket& operator=(const Socket&)	= delete;

	void	makeListener(uint16_t port);
	// void	makeConnector(const std::string& host, uint16_t port);

	Socket accept(); // call only on listening socket

	ssize_t send(std::string_view data) const;
	ssize_t receive(std::string& buffer) const;

	int  getFd()       const noexcept { return fd_; }
	bool isListening() const noexcept { return isListening_; }

private:
	int			fd_;
	sockaddr_in	addr_;
	bool		isListening_;

	// void setNonBlocking();
	// void doBind(uint16_t port);
	// void doListen();
	// void doConnect(const std::string& host, uint16_t port);
};

#endif

