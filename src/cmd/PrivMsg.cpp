#include "../../inc/irc.hpp"

void Server::cmdPrivMsg(int fd, const std::string& message) {
	std::stringstream ss(message);
	std::string cmd, target;
	ss >> cmd >> target;

	size_t colonPos = message.find(":", 1);
	if (target.empty() || colonPos == std::string::npos) {
		send(fd, ":localhost 411 * :No recipient given (PRIVMSG)\r\n", 46, 0);
		return;
	}

	std::string msgText = message.substr(colonPos + 1);

	if (target[0] == '#') {
		// Message to channel
		if (channels_.find(target) == channels_.end() || !channels_[target].hasClient(fd)) {
			std::string msg = ":localhost 442 * " + target + " :You're not on that channel\r\n";
			send(fd, msg.c_str(), msg.length(), 0);			
			return;
		}
		std::string nick = clients_[fd].nick;
		channels_[target].broadcast(fd, msgText, nick, fd);
	} else {
		// TODO: Message to another user (by nickname)
	}
}
