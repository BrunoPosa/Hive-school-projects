#include "../inc/irc.hpp"

void Server::processCommand(int fd, const std::string& message) {
	if (message.find("NICK ") == 0) {
		cmdNick(fd, message);
	} else if (message.find("USER ") == 0) {
		cmdUser(fd, message);
	} else if (message.find("PING ") == 0) {
		std::string pong = "PONG " + message.substr(5) + "\r\n";
		send(fd, pong.c_str(), pong.size(), 0);
	} else if (message.find("JOIN ") == 0) {
        cmdJoin(fd, message);
    } else if (message.find("PONG ") == 0) {
        // Handle PONG command (not implemented in this snippet)
    } else if (message.find("PRIVMSG ") == 0) {
        // Handle PRIVMSG command (not implemented in this snippet)
    } else if (message.find("QUIT") == 0 || message.find("exit") == 0) {
        std::cout << "QUIT command received" << std::endl;
        handleClientError(0, fd); // Handle QUIT command
    } else {
        send(fd, ":localhost 421 * :Unknown command client.cpp:21\r\n", 53, 0);
    }

	// Print client info
	std::string nickname = clients_[fd].nick;
	std::string username = clients_[fd].user;

	if (username.empty() && !clients_[fd].nameChanged) {
		username = "user" + std::to_string(fd);
	}

	struct sockaddr_in clientAddr;
	socklen_t addrLen = sizeof(clientAddr);
	getpeername(fd, (struct sockaddr*)&clientAddr, &addrLen);
	char clientIp[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIp, INET_ADDRSTRLEN);

	std::cout << nickname << " from " << clientIp
			  << " (FD " << fd << "): " << message << std::endl;
}

void Server::handleClient(size_t index) {
	char buffer[1024];
	ssize_t bytesRead = recv(pollFds_[index].fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead <= 0) {
		handleClientError(bytesRead == 0 ? 0 : errno, index);
		return;
	}

	buffer[bytesRead] = '\0'; // Null-terminate
	int fd = pollFds_[index].fd;

	// Split the input by \r\n and process each command
	std::string input(buffer);
	size_t pos = 0;
	std::string line;
	while ((pos = input.find("\r\n")) != std::string::npos) {
		line = input.substr(0, pos);
		processCommand(fd, line);
		input.erase(0, pos + 2); // Move past \r\n
	}
}
