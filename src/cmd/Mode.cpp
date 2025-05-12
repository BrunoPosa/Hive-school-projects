#include "../../inc/irc.hpp"

// Mode.cpp
void Server::cmdMode(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, target, modeStr, param;
    iss >> command >> target >> modeStr >> param;

    std::clog << "Debug: Channel: " << target << ", Mode: " << modeStr << ", Param: " << param << std::endl;

    if (target.empty() || modeStr.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS);
        return;
    }

    // Ignore user mode for now
    if (target[0] != '#') {
        std::clog << "Debug: Ignoring user mode command for now" << std::endl;
        return;
    }

    // Check if channel exists
    if (channels_.find(target) == channels_.end()) {
        ft_send(fd, ERR_NO_SUCH_CHANNEL(target));
        return;
    }

    Channel& channel = channels_[target];

    // Check if the client is an operator in the channel
    if (!channel.isOperator(fd)) {
        ft_send(fd, ERR_CHANOPRIVSNEEDED(target));
        return;
    }

    // Example: +o nick
    if (modeStr == "+o") {
        if (param.empty()) {
            ft_send(fd, ERR_NEEDMOREPARAMS);
            return;
        }

        // Find client by nickname
        int targetFd = -1;
        for (std::map<int, Client>::iterator it = clients_.begin(); it != clients_.end(); ++it) {
            if (it->second.getNick() == param) {
                targetFd = it->first;
                break;
            }
        }

        if (targetFd == -1 || !channel.hasClient(targetFd)) {
            ft_send(fd, ERR_USERNOTINCHANNEL(param, target));
            return;
        }

        channel.addOperator(targetFd);
        std::string msg = ":" + clients_[fd].getNick() + " MODE " + target + " +o " + param + "\r\n";
        channel.broadcast(fd, msg, clients_[fd].getNick());
    }
    else {
        ft_send(fd, ERR_UNKNOWNMODE(modeStr));
    }
}
