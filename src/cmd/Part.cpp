#include "../../inc/Server.hpp"

void Server::cmdPart(int fd, const t_data data) {
	std::istringstream iss(data.fullMsg);
	std::string command, channelList, reason;
	iss >> command >> channelList;
	std::getline(iss, reason);
	if (channelList.empty()) {
		ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick(), command));
		return;
	}
    // Trim leading whitespace
    size_t start = reason.find_first_not_of(' ');
    if (start != std::string::npos)
        reason = reason.substr(start);
    // Remove optional leading colon
    if (!reason.empty() && reason[0] == ':')
        reason = reason.substr(1);
    if (reason.empty()){
        reason = "leaving";
    }
	Client& client = clients_[fd];
	std::istringstream chStream(channelList);
	std::string channelName;
	while (std::getline(chStream, channelName, ',')) {
		if (channels_.find(channelName) == channels_.end()) {
			ft_send(fd, ERR_NOSUCHCHANNEL(client.getNick(), channelName));
			continue;
		}
		Channel& channel = channels_[channelName];
		if (!channel.hasClient(fd)) {
			ft_send(fd, ERR_NOTONCHANNEL(client.getNick(), channelName));
			continue;
		}
		// Send PART message before removing
		std::string prefix = ":" + client.getNick() + "!" + client.getUser() + "@localhost";
		std::string partMsg = prefix + " PART " + channelName + " :" + reason + "\r\n";
		channel.broadcastToAll(partMsg);
		// Clean up
		channel.removeClient(fd);
		client.leaveChannel(channelName);
		if (channel.getUserCount() == 0) {
			channels_.erase(channelName);
		} else if (channel.isOperator(fd)) {
			channel.removeOperator(fd);
		}
	}
}
