#include "../../inc/Server.hpp"

void Server::cmdPart(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, channelName, reason;
    iss >> command >> channelName;
    std::getline(iss, reason);

    if (channelName.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS);
        return;
    }

    if (reason.empty())
        reason = "leaving";
    else if (reason[0] == ' ')
        reason = reason.substr(1);
    if (reason[0] == ':')
        reason = reason.substr(1);

    Client& client = clients_[fd];
    std::string nick = client.getNick();
    std::string user = client.getUser();

    if (channels_.find(channelName) == channels_.end()) {
        ft_send(fd, ERR_NO_SUCH_CHANNEL(channelName));
        return;
    }

    Channel& channel = channels_[channelName];
    if (!channel.hasClient(fd)) {
        ft_send(fd, ERR_NOT_IN_CHANNEL(channelName));
        return;
    }

    // Send PART message before removing
    std::string prefix = ":" + nick + "!" + user + "@localhost";
    std::string partMsg = prefix + " PART " + channelName + " :" + reason + "\r\n";
    std::cerr << "Sending PART message: " << partMsg << std::endl;
    channel.broadcastToAll(partMsg);

    // Clean up
    channel.removeClient(fd);
    client.leaveChannel(channelName);
    if (channel.getUserCount() == 0) {
        channels_.erase(channelName); // Remove the channel if no clients left
        std::cerr << "Channel " << channelName << " removed as it is empty." << std::endl;
    } else {
        // If the client was an operator, remove operator status
        if (channel.isOperator(fd)) {
            channel.removeOperator(fd);
            std::cerr << "Removed operator status for FD: " << fd << " in channel: " << channelName << std::endl;
        }
    }
}

