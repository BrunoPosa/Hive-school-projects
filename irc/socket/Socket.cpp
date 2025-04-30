
#include "Socket.hpp"

using std::string;
using std::cerr;
using std::cout;
using std::endl;

Socket::Socket()
:	fd_{::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP)},
	addr_{},
	isListening_{false}
{
	if (fd_ < 0) {
		throw std::system_error(errno, std::generic_category(), "socket() failed");
	}
}

Socket::Socket(int fd, sockaddr_in addr, bool isListener) noexcept
	: fd_{fd}, addr_{addr}, isListening_{isListener} {}

Socket::Socket(Socket&& other) noexcept
: fd_(other.fd_), addr_(other.addr_), isListening_(other.isListening_)
{
	other.fd_ = -1;
	other.addr_ = sockaddr_in{};
	other.isListening_ = false;
}

Socket& Socket::operator=(Socket&& other) noexcept {
	if (this != &other) {
		if (fd_ >= 0) {
			::close(fd_);
		}
		fd_ = other.fd_;
		addr_ = other.addr_;
		isListening_ = other.isListening_;
		other.fd_ = -1;
		other.addr_ = sockaddr_in{};
		other.isListening_ = false;
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

std::optional<Socket> Socket::accept() const {
	assert(isListening_ && "Only a listening socket can call accept()");

	sockaddr_in clientAddr{};
	socklen_t addrLen = sizeof(clientAddr);

	while (true) {
		int clientFd = ::accept4(fd_, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen,
								 SOCK_NONBLOCK | SOCK_CLOEXEC);
		if (clientFd >= 0) {
			return Socket(clientFd, clientAddr, false);
		}
		switch (errno) {
			case EINTR:
				// Interrupted by signal, retry
				continue;
			case EAGAIN:
			case EWOULDBLOCK:
			case ECONNABORTED:
			case ENETDOWN:
			case EPROTO:
			case ENOPROTOOPT:
			case EHOSTDOWN:
			case ENONET:
			case EHOSTUNREACH:
			case EOPNOTSUPP:
			case ENETUNREACH:
				// Transient/network errors: no connection or aborted, return empty
				return std::nullopt;
			default:
				// Fatal errors
				throw std::system_error(errno, std::generic_category(), "accept() failed");
		}
	}
}

ssize_t Socket::send(std::string_view data) const {
	assert(fd_ >= 0 && "Send on invalid socket");
	ssize_t n = ::send(fd_, data.data(), data.size(), 0);
	if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
		throw std::system_error(errno, std::generic_category(), "send() failed");
	}
	return n; // -1 on EAGAIN/EWOULDBLOCK, or bytes written
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
