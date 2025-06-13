#include "../../inc/Server.hpp"

void Server::cmdPing(int fd, const t_data& data) {
	std::istringstream iss(data.fullMsg);
	std::string command, token;
	iss >> command;
	std::getline(iss, token);
	// Trim leading space and optional colon
	if (!token.empty() && token[0] == ' ')
		token = token.substr(1);
	if (!token.empty() && token[0] == ':')
		token = token.substr(1);
	if (token.empty()) {
		ft_send(fd, ERR_NOORIGIN);
		return;
	}
	std::string pongResponse = ":localhost PONG localhost :" + token + "\r\n";
	ft_send(fd, pongResponse);
}


