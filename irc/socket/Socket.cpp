
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

Socket::Socket(int fd, sockaddr_in addr)
:	fd_{fd}, addr_{addr}, isListening_{false} {
	if (fd_ < 0) {
		throw std::system_error(errno, std::generic_category(), "socket(fd, addr) must have positive fd");
	}
}

Socket::Socket(Socket&& other) noexcept
: fd_{other.fd_}, addr_{other.addr_}, isListening_{other.isListening_}
{
	other.fd_ = -1;
	other.addr_ = {};
	other.isListening_ = false;
}

Socket&	Socket::operator=(Socket&& other) noexcept {
	if (this != &other) {
		if (fd_ >= 0) {
			if (::close(fd_) < 0) {
				cerr << "Failed to close fd " << fd_ << ": " << std::strerror(errno) << endl;
			}
		}
		fd_ = std::exchange(other.fd_, -1);
		addr_ = std::move(other.addr_);
		isListening_ = std::exchange(other.isListening_, false);
	
		other.addr_ = {};
	}
	return *this;
}

Socket::~Socket() noexcept {
	if (fd_ >= 0) {
		if (::close(fd_) < 0) {
			cerr << "Failed to close fd " << fd_ << ": " << std::strerror(errno) << endl;
		}
		fd_ = -1;
		// cout << "closed socket" << endl;
	}
}

void	Socket::makeListener(uint16_t port) {
	if (port < 1024) {
		throw std::logic_error("Listener port must be valid");
	}

	// Enable SO_REUSEADDR to avoid "address in use" errors on server restarting gracefully via same port
	int opt = 1;
    if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::system_error(errno, std::generic_category(), "setsockopt(SO_REUSEADDR) failed");
    }

	addr_ = {};
	addr_.sin_family      = AF_INET;
	addr_.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_.sin_port        = htons(port);

	if (::bind(fd_, reinterpret_cast<sockaddr*>(&addr_), sizeof(addr_)) < 0) {
		throw std::system_error(errno, std::generic_category(), "bind() failed");
	}
	if (::listen(fd_, SOMAXCONN) < 0) {
		throw std::system_error(errno, std::generic_category(), "listen() failed");
	}
	isListening_ = true;
}

bool	Socket::accept(Socket& toSocket) const {
	if (!isListening_) {
		throw std::logic_error("accept() can be called only on the listening socket");
	}

	sockaddr_in clientAddr{};
	socklen_t addrLen = sizeof(clientAddr);
	int clientFd = ::accept4(fd_, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen, SOCK_NONBLOCK);
	if (clientFd < 0) {
		return false;
	}
	toSocket = Socket(clientFd, clientAddr);
	return true;
}

size_t Socket::send(std::string_view data) const {
	size_t totalSent = 0;
	while (totalSent < data.size()) {
		ssize_t n = ::send(fd_, data.data() + totalSent, data.size() - totalSent, MSG_NOSIGNAL);
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
