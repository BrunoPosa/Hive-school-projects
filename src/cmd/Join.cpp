#include "../../inc/irc.hpp"

void Server::cmdJoin(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, channel, key;
    iss >> command >> channel >> key;

    if (channel.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS);
        return;
    }

    Channel* chanPtr = nullptr;

    // Create the channel if it doesn't exist
    if (channels_.find(channel) == channels_.end()) {
        channels_[channel] = Channel(channel);
        channels_[channel].addOperator(fd);
    }

    chanPtr = &channels_[channel];

    // Already in the channel?
    if (clients_[fd].isInChannel(channel)) {
        ft_send(fd, ERR_USERONCHANNEL(channel));
        return;
    }

    // Invite-only (+i)?
    if (chanPtr->getInviteOnly() && !chanPtr->getIsUserInvited(fd)) {
        ft_send(fd, ERR_INVITEONLYCHAN(channel));
        return;
    }

    // Password-protected (+k)?
    if (chanPtr->hasPassword()) {
        if (key.empty() || key != chanPtr->getPwd()) {
            ft_send(fd, ERR_BADCHANNELKEY(channel));
            return;
        }
    }

    // User limit (+l)?
    if (chanPtr->hasUserLimit() && chanPtr->getUserCount() >= chanPtr->getUserLimit()) {
        ft_send(fd, ERR_CHANNELISFULL(channel));
        return;
    }

    // All checks passed, allow the user to join
    clients_[fd].joinChannel(channel, false);
    chanPtr->addClient(fd);

    std::cerr << "Client " << clients_[fd].getNick() << " joined channel: " << channel << std::endl;

    std::string joinMessage = ":" + clients_[fd].getNick() + " JOIN :" + channel + "\r\n";
    chanPtr->broadcast(fd, joinMessage, clients_[fd].getNick(), -1);
}

