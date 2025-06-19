#include "../../inc/Server.hpp"

namespace {
	bool isValidInt(const std::string& s) {
		if (s.empty()) return false;
		for (size_t i = 0; i < s.size(); ++i) {
			if (!std::isdigit(static_cast<unsigned char>(s[i]))) {
				return false;
			}
		}
		return true;
	}
}

void Server::handlePositiveMode(int fd, const std::string& command, const std::string& target,
                                const std::string& modeStr, const std::string& param, Channel& channel) {
    if (modeStr == "+i") {
        channel.setInviteOnly(true);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " +i\r\n");
    } else if (modeStr == "+t") {
        channel.setTopicRestrictedToOperators(true);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " +t\r\n");
    } else if (modeStr == "+k") {
        if (param.empty() || cfg_.isValidPassword_(param) == false) {
            ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick(),command));
            return;
        }
        channel.setPassword(param);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " +k " + param + "\r\n");
    } else if (modeStr == "+o") {
        int targetFd = channel.getClientFdByNick(param, clients_);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(param, target));
            return;
        }
        channel.addOperator(targetFd);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " +o\r\n");
	} else if (modeStr == "+l") {
		try {
			if (!isValidInt(param)) {
				throw std::invalid_argument("not a valid integer");
			}
			int limit = std::stoi(param);
			if (limit < 0) {
				throw std::invalid_argument("negative limit");
			}
			channel.setUserLimit(limit);
			channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " +l " + param + "\r\n");
        } catch (const std::exception& e) {
            ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick(), command));
            return;
        }
    } else {
        ft_send(fd, ERR_UNKNOWNMODE(clients_[fd].getNick() ,modeStr));
    }
}

void Server::handleNegativeMode(int fd, const std::string& target,
                                const std::string& modeStr, const std::string& param, Channel& channel) {
    if (modeStr == "-i") {
        channel.setInviteOnly(false);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " -i\r\n");
    } else if (modeStr == "-t") {
        channel.setTopicRestrictedToOperators(false);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " -t\r\n");
    } else if (modeStr == "-k") {
        channel.setPassword("");
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " -k\r\n");
    } else if (modeStr == "-o") {
        int targetFd = channel.getClientFdByNick(param, clients_);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(param, target));
            return;
        }
        channel.removeOperator(targetFd);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + " -o\r\n");
    } else if (modeStr == "-l") {
        channel.setUserLimit(-1);
        channel.broadcastToAll(":" + clients_[fd].getFullId() + " MODE " + target + param + " -l\r\n");
    } else {
        ft_send(fd, ERR_UNKNOWNMODE(clients_[fd].getNick(), modeStr));
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

void Server::cmdMode(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, target, modeStr, param;
    iss >> command >> target >> modeStr >> param;
    if (target.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick(), command));
        return;
    }
    // Check if it is only MODE + channel to show the channel's current modes
    if (modeStr.empty() && channels_.find(target) != channels_.end()) {
        std::string currentModes = channels_[target].getModeString();
        std::string nick = clients_[fd].getNick();
        ft_send(fd, RPL_CHANNELMODEIS(clients_[fd].getFullId(), target, currentModes, param));
        return;
    }
    Client& sender = clients_[fd];
    // Check if the Mode is targeting a user and not a channel
    if (target.empty() || target[0] != '#') {
        if (clients_[fd].getNick() == target)
            return; 
        ft_send(fd, ERR_NOSUCHCHANNEL(sender.getNick(), target));
        return;
    }
    // Check if channel exists
    if (channels_.find(target) == channels_.end()) {
        ft_send(fd, ERR_NOSUCHCHANNEL(sender.getNick(), target));
        return;
    }
    // Check if the client is an operator in the channel
    if (!channels_[target].isOperator(fd)) {
        ft_send(fd, ERR_CHANOPRIVSNEEDED(sender.getNick(),target));
        return;
    }
    Channel& channel = channels_[target];
    if (modeStr[0] == '+') {
        handlePositiveMode(fd, command, target, modeStr, param, channel);
    } else if (modeStr[0] == '-') {
        handleNegativeMode(fd, target, modeStr, param, channel);
    } else {
		return;
    }
}
