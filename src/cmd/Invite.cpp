#include "../../inc/Server.hpp"

void Server::cmdInvite(int sender_fd, const t_data data) {
    std::vector<std::string> params{data.cmdParams};
    if (params.size() < 2) {
        ft_send(sender_fd, ERR_NEEDMOREPARAMS);
        return;
    }

    const std::string& channelName = params[0];
    const std::string& targetNick = params[1];

    if (channels_.find(channelName) == channels_.end()) {
        ft_send(sender_fd, ERR_NO_SUCH_CHANNEL(channelName));
        return;
    }

    Channel& channel = channels_[channelName];
    Client& sender = clients_[sender_fd];

    if (!sender.isInChannel(channelName)) {
        ft_send(sender_fd, ERR_NOT_IN_CHANNEL(channelName));
        return;
    }

    if (!channel.isOperator(sender_fd)) {
        ft_send(sender_fd, ERR_CHANOPRIVSNEEDED(channelName));
        return;
    }

    // Find target client's fd by nickname
    int target_fd = channel.getClientFdByNick(targetNick, clients_);
    if (target_fd == -1) {
        ft_send(sender_fd, ERR_NOSUCHNICK(targetNick));
        return;
    }

    // Add the target client to the invited list
    if (!channel.getIsUserInvited(target_fd)) {
        channel.addInvitedUser(target_fd);
    }

    // Notify the sender that the invite was sent
    ft_send(sender_fd, RPL_INVITING(sender.getNick(), targetNick, channelName));

    // Optionally send invitation message to the invited client
    std::string inviteMsg = ":" + sender.getNick() + " INVITE " + targetNick + " :" + channelName + "\r\n";
    ft_send(target_fd, inviteMsg);
}
