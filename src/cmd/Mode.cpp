#include "../../inc/Server.hpp"

void Server::handlePositiveMode(int fd, const std::string& command, const std::string& target,
                                const std::string& modeStr, const std::string& param, Channel& channel) {
    if (modeStr == "+i") {
        channel.setInviteOnly(true);
        ft_send(fd, RPL_MODESET(target, "+i"));
    } else if (modeStr == "+t") {
        channel.setTopicRestrictedToOperators(true);
        ft_send(fd, RPL_MODESET(target, "+t"));
    } else if (modeStr == "+k") {
        if (param.empty()) {
            ft_send(fd, ERR_NEEDMOREPARAMS(command));
            return;
        }
        channel.setPassword(param);
        ft_send(fd, RPL_MODESET(target, "+k " + param));
    } else if (modeStr == "+o") {
        int targetFd = channel.getClientFdByNick(param, clients_);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(param));
            return;
        }
        channel.addOperator(targetFd);
        ft_send(fd, RPL_MODESET(target, "+o " + param));
    } else if (modeStr == "+l") {
        int limit = std::stoi(param);
        channel.setUserLimit(limit);
        ft_send(fd, RPL_MODESET(target, "+l " + param));
    } else {
        ft_send(fd, ERR_UNKNOWNMODE(modeStr));
    }
}

void Server::handleNegativeMode(int fd, const std::string& target,
                                const std::string& modeStr, const std::string& param, Channel& channel) {
    if (modeStr == "-i") {
        channel.setInviteOnly(false);
        ft_send(fd, RPL_MODESET(target, "-i"));
    } else if (modeStr == "-t") {
        channel.setTopicRestrictedToOperators(false);
        ft_send(fd, RPL_MODESET(target, "-t"));
    } else if (modeStr == "-k") {
        channel.setPassword("");
        ft_send(fd, RPL_MODESET(target, "-k"));
    } else if (modeStr == "-o") {
        int targetFd = channel.getClientFdByNick(param, clients_);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(param));
            return;
        }
        channel.removeOperator(targetFd);
        ft_send(fd, RPL_MODESET(target, "-o " + param));
    } else if (modeStr == "-l") {
        channel.setUserLimit(-1);
        ft_send(fd, RPL_MODESET(target, "-l"));
    } else {
        ft_send(fd, ERR_UNKNOWNMODE(modeStr));
    }
}

std::string Channel::getModeString() const {
    std::string mode = "+";

    if (getInviteOnly())
        mode += "i";
    if (getTopicRestricted())
        mode += "t";
    if (hasPassword())
        mode += "k";
    if (hasUserLimit())
        mode += "l";

    return (mode == "+" ? "" : mode);
}


// Mode.cpp
void Server::cmdMode(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, target, modeStr, param;
    iss >> command >> target >> modeStr >> param;
    std::clog << "Debug: Channel: " << target << ", Mode: " << modeStr << ", Param: " << param << std::endl;

    if (target.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS(command));
        return;
    }

    if (modeStr.empty()) {
        Channel& channel = channels_[target];
        std::string currentModes = channel.getModeString(); // e.g., "+it"
        ft_send(fd, ":localhost MODE " + target + " " + currentModes + "\r\n");
        return;
    }
    
    if (target[0] != '#') {
        std::clog << "Debug: Ignoring user mode command for now" << std::endl;
        return;
    }
    
    if (channels_.find(target) == channels_.end()) {
        ft_send(fd, ERR_NOSUCHCHANNEL(target));
        return;
    }

    // Ignore user mode for now


    // Check if channel exists
    if (channels_.find(target) == channels_.end()) {
        ft_send(fd, ERR_NOSUCHCHANNEL(target));
        return;
    }
    Channel& channel = channels_[target];

    // Check if the client is an operator in the channel
    if (!channel.isOperator(fd)) {
        ft_send(fd, ERR_CHANOPRIVSNEEDED(target));
        return;
    }

    if (modeStr[0] == '+') {
        handlePositiveMode(fd, command, target, modeStr, param, channel);
    } else if (modeStr[0] == '-') {
        handleNegativeMode(fd, target, modeStr, param, channel);
    } else {
        ft_send(fd, ERR_UNKNOWNMODE(modeStr));
    }
}