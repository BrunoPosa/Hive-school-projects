#include "../../inc/Server.hpp"

void Server::cmdPrivMsg(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, target, msgPart;
    iss >> command >> target;

    // Check missing target
    if (target.empty()) {
        ft_send(fd, ERR_NORECIPIENT);
        return;
    }

    // Read remainder of message
    std::getline(iss, msgPart);
    if (msgPart.empty() || msgPart == " :" || msgPart == ":") {
        ft_send(fd, ERR_NOTEXTTOSEND);
        return;
    }

    // Clean leading space and colon
    if (!msgPart.empty() && msgPart[0] == ' ')
        msgPart = msgPart.substr(1);
    if (!msgPart.empty() && msgPart[0] == ':')
        msgPart = msgPart.substr(1);

    Client &sender = clients_[fd];
    std::string prefix = ":" + sender.getNick() + "!" + sender.getUser() + "@localhost";
    std::string fullMsg = prefix + " PRIVMSG " + target + " :" + msgPart + "\r\n";

    // ---------------------------
    // Channel message
    // ---------------------------
    if (target[0] == '#') {
        if (channels_.find(target) == channels_.end()) {
            ft_send(fd, ERR_NOSUCHCHANNEL(target));
            return;
        }

        Channel &channel = channels_[target];

        // Check invite-only mode
        if (channel.getInviteOnly() && !channel.getIsUserInvited(fd) && !sender.isInChannel(target)) {
            ft_send(fd, ERR_CANNOTSENDTOCHAN(target));
            return;
        }

        // Check if sender is in channel
        if (!sender.isInChannel(target)) {
            ft_send(fd, ERR_NOTONCHANNEL(target));
            return;
        }

        // Broadcast message to all members except the sender
        channel.broadcast(fullMsg, sender.getNick(), fd);
    }

    // ---------------------------
    // Private message
    // ---------------------------
    else {
        int targetFd = getClientFdByNick(target);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(target));
            return;
        }
        ft_send(targetFd, fullMsg);
    }
}

