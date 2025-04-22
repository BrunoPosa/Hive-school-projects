#include "../../inc/irc.hpp"


void Server::cmdJoin(int fd, const std::string& message) {
	std::cout << "received JOIN command " << message << " FD: " << fd << std::endl;

	std::stringstream ss(message);
	std::string cmd, channelName;
	ss >> cmd >> channelName;

	if (channelName.empty() || channelName[0] != '#') {
		std::string errorMsg = ":localhost 403 * " + channelName + " :No such channel\r\n";
		send(fd, errorMsg.c_str(), errorMsg.length(), 0);
		return;
	}

	// Create channel if it doesn't exist
	if (channels_.find(channelName) == channels_.end()) {
		channels_[channelName] = Channel(channelName);
	}

	// Add client to channel and update client state
	channels_[channelName].addClient(fd);
	clients_[fd].joinChannel(channelName); // optional, if you're tracking which channels the client is in

	// Notify the user that they joined
	std::string joinMsg = ":" + clients_[fd].nick + " JOIN " + channelName + "\r\n";
	send(fd, joinMsg.c_str(), joinMsg.length(), 0);

	// Broadcast to everyone else in the channel
	channels_[channelName].broadcast(fd, "has joined the channel", clients_[fd].nick, fd);
}