
#include "../inc/Socket.hpp"
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

using std::string;
using std::cerr;
using std::cout;
using std::endl;

Socket::Socket() : fd_{-1}, addr_{}, isListening_{false} {
	fd_ = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	if (fd_ < 0) {
		throw std::system_error(errno, std::generic_category(), "socket() failed");
	}
}

Socket::Socket(int fd, sockaddr_in addr, bool isListener) noexcept
	: fd_{fd}, addr_{addr}, isListening_{isListener} {}

Socket::Socket(Socket&& obj) noexcept
: fd_(obj.fd_), addr_(obj.addr_), isListening_(obj.isListening_)
{
	obj.fd_ = -1;
}

Socket& Socket::operator=(Socket&& other) noexcept {
	if (this != &other) {
		// Clean up our current socket descriptor if valid.
		if (fd_ >= 0) {
			::close(fd_);
		}

		// Transfer ownership from 'other' to this instance.
		fd_ = other.fd_;
		addr_ = other.addr_;
		isListening_ = other.isListening_;

		// Leave 'other' in a safe state.
		other.fd_ = -1;
	}
	return *this;
}

Socket::~Socket() {
	if (fd_ >= 0) {
		if (::close(fd_) < 0) {
			cerr << "Failed to close fd " << fd_ << ": " << std::strerror(errno) << endl;
		}
		fd_ = -1;
	}
}

void	Socket::makeListener(uint16_t port) {
	addr_.sin_family      = AF_INET;
	addr_.sin_addr.s_addr = INADDR_ANY;
	addr_.sin_port        = htons(port);

	if (::bind(fd_, reinterpret_cast<sockaddr*>(&addr_), sizeof(addr_)) < 0) {
		throw std::system_error(errno, std::generic_category(), "bind() failed");
	}

	if (::listen(fd_, SOMAXCONN) < 0) {
		throw std::system_error(errno, std::generic_category(), "listen() failed");
	}
	isListening_ = true;
}

//
// Public API
//
Socket Socket::accept() const {
	assert(isListening_ && "Only listening sockets can call accept()");
	sockaddr_in cli{};
	socklen_t sz = sizeof(cli);

	int clientFd = ::accept4(fd_, reinterpret_cast<sockaddr*>(&cli), &sz, O_NONBLOCK);
	if (clientFd < 0) {
		if (errno == EWOULDBLOCK || errno == EAGAIN) {
			cout << "accept() would block" << endl;
		} else {
			throw std::system_error(errno, std::generic_category(), "accept() failed");//maybe we need not throw?
		}
	}
	return Socket(clientFd, cli, false);
}

ssize_t Socket::send(std::string_view data) const {
	assert(fd_ >= 0 && "Send on invalid socket");
	size_t sent = 0;
	while (sent < data.size()) {
		ssize_t n = ::send(fd_,
						data.data() + sent,
						data.size() - sent,
						0);
		if (n < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			throw std::system_error(errno, std::generic_category(), "send() failed");
		}
		sent += n;
	}
	return static_cast<ssize_t>(sent);
}

ssize_t Socket::receive(string& buf) const {
	assert(fd_ >= 0 && "Recieve on invalid socket");
	char tmp[4096];
	ssize_t n = ::recv(fd_, tmp, sizeof(tmp), 0);
	if (n < 0) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return 0;
		throw std::system_error(errno, std::generic_category(), "recv() failed");
	}
	if (n > 0)
		buf.assign(tmp, static_cast<size_t>(n));
	return n;
}
