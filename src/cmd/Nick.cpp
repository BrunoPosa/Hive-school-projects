#include "../../inc/Server.hpp"

namespace {
    bool isValidNick(const std::string& nick) {
        if (nick.empty())
            return false;
        const std::string special = "[]\\`_^{|}";
        char first = nick[0];
        if (!std::isalpha(first) && special.find(first) == std::string::npos)
            return false;
        // Rest of the nickname: can include letter, digit, special, or '-'
        for (size_t i = 1; i < nick.size(); ++i) {
            char c = nick[i];
            if (!std::isalnum(c) &&
                special.find(c) == std::string::npos &&
                c != '-') {
                return false;
            }
        }
        return true;
    }
    bool isNickInUse(const std::map<int, Client>& clients, const std::string& nick, int excludeFd) {
        for (const auto& pair : clients) {
            if (pair.first != excludeFd && pair.second.getNick() == nick)
                return true;
        }
        return false;
    }
}

void Server::cmdNick(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, nick;
    iss >> command >> nick;
    if (nick.empty()) {
        std::string errorMsg = ERR_NO_NICKNAME(clients_[fd].getNick());
        ft_send(fd, errorMsg);
        return;
    }
    if (nick.length() > 15) {
        std::string errorMsg = ERR_ERRONEOUS_NICKNAME(nick);
        ft_send(fd, errorMsg);
        return;
    }
    if (!isValidNick(nick)) {
        std::string errorMsg = ERR_ERRONEOUS_NICKNAME(nick);
        ft_send(fd, errorMsg);
        return;
    }
    if (clients_[fd].isAuthenticated()) {
        if (isNickInUse(clients_, nick, fd)) {
            ft_send(fd, ERR_NICK_IN_USE(clients_[fd].getUser(), nick));
            return;
        }
    } else {
        while (isNickInUse(clients_, nick, fd)) {
            nick += "_";
        }
    }
    std::string oldNick = clients_[fd].getNick();
	if (oldNick == nick){
		return;
	}
    clients_[fd].setNick(nick);
    if (clients_[fd].hasReceivedUser() && clients_[fd].isAuthenticated() && !clients_[fd].hasReceivedNick()) {
        ft_send(fd, RPL_WELCOME(nick));
    }
	clients_[fd].setNickReceived();
    // Broadcast nick change to all unique clients INCLUDING the sender
    std::set<int> notifiedClients;
    std::string msg = ":" + oldNick + " NICK :" + nick + "\r\n";
    // Always notify the sender too
    clients_[fd].toSend(msg.c_str());
    notifiedClients.insert(fd);
    for (std::map<std::string, Channel>::iterator it = channels_.begin(); it != channels_.end(); ++it) {
        if (!it->second.isEmpty()) {
            for (int otherFd : it->second.getChClients()) {
                if (notifiedClients.insert(otherFd).second) {
                    clients_[otherFd].toSend(msg.c_str());
                }
            }
        }
    }
}
