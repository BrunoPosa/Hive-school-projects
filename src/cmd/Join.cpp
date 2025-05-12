#include "../../inc/irc.hpp"


void Server::cmdJoin(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, channel;
    iss >> command >> channel;

    if (channel.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS);
        return;
    }

    // If channel doesn't exist, create and auto-op
    if (channels_.find(channel) == channels_.end()) {
        channels_[channel] = Channel(channel);
        channels_[channel].addOperator(fd);
    } else {
        // If invite-only and not invited, reject
        if (channels_[channel].getInviteOnly() && !channels_[channel].getIsUserInvited(fd)) {
            ft_send(fd, ERR_CHANOPRIVSNEEDED(channel));
            return;
        }

        // Already in the channel?
        if (clients_[fd].isInChannel(channel)) {
            ft_send(fd, ERR_USERONCHANNEL(channel));
            return;
        }
    }

    // Passed all checks — join
    std::cerr << "Client " << clients_[fd].getNick() << " joined channel: " << channel << std::endl;
    clients_[fd].joinChannel(channel, false);
    channels_[channel].addClient(fd);

    std::string joinMessage = ":" + clients_[fd].getNick() + " JOIN :" + channel + "\r\n";
    channels_[channel].broadcast(fd, joinMessage, clients_[fd].getNick(), -1);
}

