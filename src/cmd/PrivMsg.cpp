#include "../../inc/Server.hpp"

void Server::cmdPrivMsg(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, target, msgPart;
    iss >> command >> target;

    if (target.empty()) {
        ft_send(fd, ERR_NO_RECIPIENT);
        return;
    }

    std::getline(iss, msgPart); // Get message after the target

    if (msgPart.empty() || msgPart == " :" || msgPart == ":") {
        ft_send(fd, ERR_NO_TEXT_TO_SEND);
        return;
    }

    // Clean up leading space and colon
    if (msgPart[0] == ' ')
        msgPart = msgPart.substr(1);
    if (msgPart[0] == ':')
        msgPart = msgPart.substr(1);

    // ✅ Always get sender from FD, not from any string in message
    Client &sender = clients_[fd];
    std::string prefix = ":" + sender.getNick() + "!" + sender.getUser() + "@localhost";
    std::string fullMsg = prefix + " PRIVMSG " + target + " :" + msgPart + "\r\n";

    // Send to channel
    if (target[0] == '#') {
        if (channels_.find(target) == channels_.end()) {
            ft_send(fd, ERR_NO_SUCH_CHANNEL(target));
            return;
        }
        if (!sender.isInChannel(target)) {
            ft_send(fd, ERR_NOT_IN_CHANNEL(target));
            return;
        }

        channels_[target].broadcast(fullMsg, clients_[fd].getNick(), fd);
    } else {
        // It's a private message to a user
        int targetFd = getClientFdByNick(target);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(target));
            return;
        }
        ft_send(targetFd, fullMsg);
    }
}
