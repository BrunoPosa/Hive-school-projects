#include "../../inc/Server.hpp"

void Server::cmdJoin(int fd, const std::string& message)
{
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
        channels_[channel] = Channel(channel, &clients_);
        channels_[channel].addOperator(fd);
        std::cerr << "added operator " << fd << " to channel " << channel << std::endl;
    }

    chanPtr = &channels_[channel];
    // Already in the channel?
    if (clients_[fd].isInChannel(channel)) {
        ft_send(fd, ERR_USERONCHANNEL(channel));
        return;
    }

    std::cerr << "Channel invite-only: " << chanPtr->getInviteOnly() << std::endl;
    std::cerr << "Is user invited? " << chanPtr->getIsUserInvited(fd) << std::endl;

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

    // Send topic info after successful join
    if (!chanPtr->getTopic().empty()) {
        ft_send(fd, RPL_TOPIC(clients_[fd].getNick(), channel, chanPtr->getTopic()));
    } else {
        ft_send(fd, RPL_NOTOPIC(clients_[fd].getNick(), channel));
    }

    std::string prefix = ":" + clients_[fd].getNick() + "!" + clients_[fd].getUser() + "@localhost";
    std::string joinMessage = prefix + " JOIN :" + channel + "\r\n";
    chanPtr->broadcast(joinMessage, clients_[fd].getNick(), -1);

    clients_[fd].toSend(IrcMessages::RPL_NAMREPLY(clients_[fd].getNick(), chanPtr, &clients_) + IrcMessages::RPL_ENDOFNAMES(clients_[fd].getNick(), chanPtr));
}