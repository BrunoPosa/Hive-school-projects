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
        std::cerr << "target: " << target << std::endl;
        channel.setInviteOnly(true);
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " +i\r\n";
        channel.broadcastToAll(msg);
    } else if (modeStr == "+t") {
        channel.setTopicRestrictedToOperators(true);
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " +t\r\n";
        channel.broadcastToAll(msg);
    } else if (modeStr == "+k") {
        if (param.empty()) {
            ft_send(fd, ERR_NEEDMOREPARAMS(clients_[fd].getNick(),command));
            return;
        }
        channel.setPassword(param);
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " +k\r\n";
        channel.broadcastToAll(msg);
    } else if (modeStr == "+o") {
        int targetFd = channel.getClientFdByNick(param, clients_);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(param, target));
            return;
        }
        channel.addOperator(targetFd);
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " +o\r\n";
        channel.broadcastToAll(msg);
	} else if (modeStr == "+l") {
		try {
			// Check if the string contains only digits (optionally with a leading '+')
			if (!isValidInt(param)) {
				throw std::invalid_argument("not a valid integer");
			}
			int limit = std::stoi(param);
			if (limit < 0) {
				throw std::invalid_argument("negative limit");
			}
			channel.setUserLimit(limit);
			std::string fullId = clients_[fd].getFullId(); // nick!user@host
			std::string msg = ":" + fullId + " MODE " + target + " +l " + param + "\r\n";
			channel.broadcastToAll(msg);
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
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " -i\r\n";
        channel.broadcastToAll(msg);
    } else if (modeStr == "-t") {
        channel.setTopicRestrictedToOperators(false);
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " -t\r\n";
        channel.broadcastToAll(msg);
    } else if (modeStr == "-k") {
        channel.setPassword("");
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " -k\r\n";
        channel.broadcastToAll(msg);
    } else if (modeStr == "-o") {
        int targetFd = channel.getClientFdByNick(param, clients_);
        if (targetFd == -1) {
            ft_send(fd, ERR_NOSUCHNICK(param, target));
            return;
        }
        channel.removeOperator(targetFd);
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + " -o\r\n";
        channel.broadcastToAll(msg);
    } else if (modeStr == "-l") {
        channel.setUserLimit(-1);
        std::string fullId = clients_[fd].getFullId(); // nick!user@host
        std::string msg = ":" + fullId + " MODE " + target + param + " -l\r\n";
        channel.broadcastToAll(msg);
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
    if (modeStr.empty() && channels_[target].getName() == target) {
        std::string currentModes = channels_[target].getModeString(); // e.g., "+nt"
        std::string nick = clients_[fd].getNick();          // The user's nick
        // Send RPL_CHANNELMODEIS (324)
        ft_send(fd, RPL_CHANNELMODEIS(clients_[fd].getNick(), target, currentModes, param));
        return;
    }
    Client& sender = clients_[fd];
    if (target.empty() || target[0] != '#') {
    std::cerr << "nick: " << clients_[fd].getNick() << std::endl;
    std::cerr << "targ: " << target << std::endl;
        if (clients_[fd].getNick() == target)
            return; 
    ft_send(fd, ERR_NOSUCHCHANNEL(sender.getNick(), target));
    return;
    }
    if (channels_.find(target) == channels_.end()) {
        ft_send(fd, ERR_NOSUCHCHANNEL(sender.getNick(), target));
        return;
    }
    // Check if channel exists
    if (channels_.find(target) == channels_.end()) {
        ft_send(fd, ERR_NOSUCHCHANNEL(sender.getNick(), target));
        return;
    }
    Channel& channel = channels_[target];
    // Check if the client is an operator in the channel
    if (!channel.isOperator(fd)) {
        ft_send(fd, ERR_CHANOPRIVSNEEDED(sender.getNick(),target));
        return;
    }
    if (modeStr[0] == '+') {
        handlePositiveMode(fd, command, target, modeStr, param, channel);
    } else if (modeStr[0] == '-') {
        handleNegativeMode(fd, target, modeStr, param, channel);
    } else {
		return;
    }
}
