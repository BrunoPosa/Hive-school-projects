
Socket Socket::accept() {
	assert(isListening_ && "Only listening sockets can call accept()");
	sockaddr_in cli{};
	socklen_t sz = sizeof(cli);
	#ifdef __linux__
		int clientFd = ::accept4(fd_, reinterpret_cast<sockaddr*>(&cli), &sz, O_NONBLOCK);
	#elif __APPLE__
		//check exact line from ft_irc subject
	#else
		int clientFd = accept(fd_, reinterpret_cast<sockaddr*>(&cli), &sz);
		if (clientFd >= 0) {
			fcntl(sock, F_SETFL, O_NONBLOCK);
		}
	#endif
	if (clientFd < 0) {
		throw std::system_error(errno, std::generic_category(), "accept() failed");
	}
	return Socket(clientFd, false);
}


Socket::Socket() : isListening_{false}, addr_{}, fd_{-1}
{
	#ifdef __linux__
	fd_ = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (fd_ < 0) {
		throw std::system_error(errno, std::generic_category(), "socket() failed");
	}
	#else
	fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd_ < 0) {
		throw std::system_error(errno, std::generic_category(), "socket() failed");
	}
	if (fcntl(fd_, F_SETFL, O_NONBLOCK) < 0) {
		throw std::system_error(errno, std::generic_category(), "failed to set non‑blocking");
	}
	#endif
}