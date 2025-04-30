
#include "../inc/Socket.hpp"

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

Socket&	Socket::operator=(Socket&& other) noexcept {
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

Socket::~Socket() noexcept {
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

bool	Socket::accept(Socket& toSocket) const noexcept {
	assert(isListening_ && "Only a listening socket can call accept()");
	assert(fd_ >= 0);

	sockaddr_in clientAddr{};
	socklen_t addrLen = sizeof(clientAddr);
	int clientFd = ::accept4(fd_, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen, SOCK_NONBLOCK);
	if (clientFd < 0) {
		return false;
	}
	toSocket = Socket(clientFd, clientAddr, false);
	return true;
}

ssize_t Socket::send(std::string_view data) const {
	assert(fd_ >= 0 && "Send on invalid socket");

	size_t totalSent = 0;
	while (totalSent < data.size()) {
		ssize_t n = ::write(fd_, data.data() + totalSent, data.size() - totalSent);
		if (n > 0) {
			totalSent += n;
		} else if (n == -1) {
			if (errno == EINTR) {
				continue;  // Interrupted; retry.
			}
			else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				break;  // Non-fatal, temporary conditions.
			}
			else {
				throw std::system_error(errno, std::generic_category(), "write() failed");// Fatal error
			}
		} else {
			break; // n == 0; break out to avoid potential infinite loop.
		}
	}
	return totalSent;
}

ssize_t Socket::receive(std::string &buf) const {
	assert(fd_ >= 0 && "Receive on invalid socket");
	char tmp[4096];
	ssize_t n = 0;

	while (true) {
		n = ::read(fd_, tmp, sizeof(tmp));
		if (n > 0) {
			break;
		} else if (n == 0) {
			break;// End-of-file: the peer has closed the connection.
		} else {
			if (errno == EINTR) { // Interrupted by a signal, retry the read.
				continue;
			} else if (errno == EAGAIN || errno == EWOULDBLOCK) { // no data available; return 0 bytes read.
				n = 0;
				break;
			} else {
				throw std::system_error(errno, std::generic_category(), "read() failed");
			}
		}
	}

	if (n > 0) {
		buf.assign(tmp, static_cast<size_t>(n));
	} else {
		buf.clear();
	}
	return n;
}
