#include "../../inc/Server.hpp"

void Server::cmdPrivMsg(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, target, msgPart;
    iss >> command >> target;
    // Check missing target
    if (target.empty()) {
        ft_send(fd, ERR_NORECIPIENT(clients_[fd].getNick()));
        return;
    }
    // Read remainder of message
    std::getline(iss, msgPart);
    if (msgPart.empty() || msgPart == " :" || msgPart == ":") {
        ft_send(fd, ERR_NOTEXTTOSEND(clients_[fd].getNick()));
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
            ft_send(fd, ERR_NOSUCHCHANNEL(sender.getNick(), target));
            return;
        }
        Channel &channel = channels_[target];
        // Check invite-only mode
        if (channel.getInviteOnly() && !channel.getIsUserInvited(fd) && !sender.isInChannel(target)) {
            ft_send(fd, ERR_CANNOTSENDTOCHAN(sender.getNick(),target));
            return;
        }
        // Check if sender is in channel
        if (!sender.isInChannel(target)) {
            ft_send(fd, ERR_NOTONCHANNEL(sender.getNick(),target));
            return;
        }
        // Broadcast message to all members except the sender
        channel.broadcast(fullMsg, sender.getNick(), fd);
    }
    // ---------------------------
    // Private message
    // ---------------------------
    else {
        std::istringstream targetStream(target);
        std::set<int> sentFds;
        std::string nick;
        while (std::getline(targetStream, nick, ',')) {
            if (nick.empty() || nick[0] == '#')
                continue; // skip channels or empty entries
            int targetFd = getClientFdByNick(nick);
            if (targetFd == -1) {
                ft_send(fd, ERR_NOSUCHNICK(sender.getNick(), nick));
                continue;
            }
            if (sentFds.insert(targetFd).second) // true if newly inserted
                ft_send(targetFd, fullMsg);
        }
    }
}

