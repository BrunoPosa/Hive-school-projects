#include "../../inc/irc.hpp"

void Server::cmdUser(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, user, mode, unused, realname;
    iss >> command >> user >> mode >> unused >> realname;

    if (user.empty() || mode.empty() || realname.empty()) {
        std::string errMsg = ERR_NOT_ENOUGH_PARAMS;
        errMsg += "Usage: USER <username> <mode> <unused> <realname>\r\n";
        ft_send(fd, errMsg);
        return;
    }    

    if (clients_[fd].hasReceivedUser()) {
        std::string errMsg = ERR_ALREADY_REGISTERED;
        ft_send(fd, errMsg);  // Use ft_send here
        return;
    }

    clients_[fd].setUser(user);
    clients_[fd].setUserReceived();
    std::string welcomeMsg = WELCOME_MSG(user);
    ft_send(fd, welcomeMsg);  // Use ft_send here
}
