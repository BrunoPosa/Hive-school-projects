#include "../../inc/Server.hpp"

// void Server::kickUser(int sender_fd, const std::string& channelName, const std::string& reason, const std::string& targetNick) {
//     Channel& channel = channels_[channelName];
//     int target_fd = channel.getClientFdByNick(targetNick, clients_);

//     if (target_fd == -1)
//         return; // Shouldn't happen if validated earlier

//     std::string message = ":" + clients_[sender_fd].getNick() + " KICK " + channelName + " " + targetNick + " :" + reason + "\r\n";

//     channel.broadcast(message, clients_[sender_fd].getNick(), -1);

//     // Remove user from channel
//     channel.removeClient(target_fd);
//     clients_[target_fd].leaveChannel(channelName);
// }
void Server::kickUser(int sender_fd, const std::string& channelName, const std::string& reason, const std::string& targetNick) {
    Channel& channel = channels_[channelName];
    int target_fd = channel.getClientFdByNick(targetNick, clients_);

    if (target_fd == -1)
        return;

    std::string message = ":" + clients_[sender_fd].getFullId() +
                          " KICK " + channelName + " " + targetNick +
                          " :" + reason + "\r\n";

    // Send to everyone in the channel, including the one being kicked
    channel.broadcastToAll(message);

    // Remove user from channel
    channel.removeClient(target_fd);
    clients_[target_fd].leaveChannel(channelName);
}


// KICK command implementation
void Server::cmdKick(int sender_fd, const t_data data) {
    std::vector<std::string> params{data.cmdParams};
    if (params.size() < 2) {
        ft_send(sender_fd, ERR_NEEDMOREPARAMS(params[0]));
        return;
    }

    const std::string& channelName = params[0];
    const std::string& targetNick = params[1];

    if (channels_.find(channelName) == channels_.end()) {
        ft_send(sender_fd, ERR_NOSUCHCHANNEL(channelName));
        return;
    }

    Channel& channel = channels_[channelName];

    if (!channel.isOperator(sender_fd)) {
        ft_send(sender_fd, ERR_CHANOPRIVSNEEDED(channelName));
        return;
    }

    int target_fd = channel.getClientFdByNick(targetNick, clients_);
    if (target_fd == -1) {
        ft_send(sender_fd, ERR_USERNOTINCHANNEL(targetNick, channelName));
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

    kickUser(sender_fd, channelName, reason, targetNick);
}
