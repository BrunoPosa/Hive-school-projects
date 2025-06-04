#include "../../inc/Server.hpp"

namespace {
        bool Server::isValidNick(const std::string& nick) {
        if (nick.empty())
            return false;

        // Disallowed first characters
        if (nick[0] == '#' || nick[0] == ':' || std::isspace(nick[0]))
            return false;

        for (char c : nick) {
            if (std::isspace(c) || c == ':' || c == ',')
                return false;

            if (!std::isalnum(c) && std::string("[]{}\\|^-_").find(c) == std::string::npos)
                return false;
        }
        return true;
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

    if (!isValidNick(nick)) {
        std::string errorMsg = ERR_ERRONEOUS_NICKNAME(nick);
        ft_send(fd, errorMsg);
        return;
    }

    for (const auto& pair : clients_) {
        if (pair.first != fd && pair.second.getNick() == nick) {
            std::string errorMsg = ERR_NICK_IN_USE(nick);
            ft_send(fd, errorMsg);
            return;
        }
    }

    clients_[fd].setNick(nick);
    clients_[fd].setNickReceived();

    std::string welcomeMsg = RPL_WELCOME(nick);
    ft_send(fd, welcomeMsg);
}

