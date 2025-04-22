#include "Socket.hpp"

using std::string;
using std::cerr;
using std::cout;
using std::endl;

Socket::Socket() : addr_{}, isListening_{false} {
	#ifdef __linux__
	fd_ = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	#else
	_fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fcntl(fd_, F_SETFL, O_NONBLOCK) < 0) {
		throw std::system_error(errno, std::generic_category(), "failed to set non‑blocking");
	}
	#endif
	if (fd_ < 0) {
		throw std::system_error(errno, std::generic_category(), "socket() failed");
	}
}

explicit Socket::Socket(int fd, bool isListener) noexcept
	: fd_{fd}, addr_{}, isListening_{isListener} {}


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

Socket Socket::accept() const {
	assert(isListening_ && "Only listening sockets can call accept()");
	sockaddr_in client{};
	socklen_t size = sizeof(client);
	int clientFd = ::accept(fd_, reinterpret_cast<sockaddr*>(&client), &size);
	if (clientFd < 0) {
		throw std::system_error(errno, std::generic_category(), "accept() failed");
	}
	// new socket inherits non‑blocking on Linux??
	return Socket(clientFd, false);
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
