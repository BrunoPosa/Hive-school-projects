#include "../../inc/irc.hpp"

void Server::cmdNick(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, nick;
    iss >> command >> nick;

    if (nick.empty()) {
        std::string errorMsg = ERR_NO_NICKNAME(clients_[fd].getNick());
        ft_send(fd, errorMsg);
        return;
    }

    // Check if the nickname is already taken by another client
    for (const auto& pair : clients_) {
        int other_fd = pair.first;
        const Client& other_client = pair.second;

        if (other_fd != fd && other_client.getNick() == nick) {
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
