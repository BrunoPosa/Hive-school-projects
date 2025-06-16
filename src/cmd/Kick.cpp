#include "../../inc/Server.hpp"

void Server::kickUser(int fd, const std::string& channelName, const std::string& reason, const std::string& targetNick) {
    Channel& channel = channels_[channelName];
    int target_fd = channel.getClientFdByNick(targetNick, clients_);
    if (target_fd == -1)
        return;
    std::string message = ":" + clients_[fd].getFullId() +
                          " KICK " + channelName + " " + targetNick +
                          " " + reason + "\r\n";
    // Send to everyone in the channel, including the one being kicked
    channel.broadcastToAll(message);
    channel.removeClient(target_fd);
    clients_[target_fd].leaveChannel(channelName);
}

void Server::cmdKick(int fd, const t_data data) {
    std::vector<std::string> params{data.cmdParams};
    if (params.size() < 2) {
        ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick() ,params[0]));
        return;
    }
    const std::string& channelName = params[0];
    const std::string& targetNick = params[1];
    if (channels_.find(channelName) == channels_.end()) {
		ft_send(fd, ERR_NOSUCHCHANNEL(clients_[fd].getNick(), channelName));
		return;
	}
    Channel& channel = channels_[channelName];
    if (!channel.isOperator(fd)) {
        ft_send(fd, ERR_CHANOPRIVSNEEDED(clients_[fd].getNick(), channelName));
        return;
    }
    int target_fd = channel.getClientFdByNick(targetNick, clients_);
    if (!clients_[target_fd].isInChannel(channelName)) {
        ft_send(fd, ERR_USERNOTINCHANNEL(targetNick, channelName));
        return;
    }
    std::string reason = targetNick;
    if (params.size() > 2) {
        reason.clear();
        for (size_t i = 2; i < params.size(); ++i) {
            if (i > 2)
                reason += " ";
            reason += params[i];
        }
    }
    kickUser(fd, channelName, reason, targetNick);
}
