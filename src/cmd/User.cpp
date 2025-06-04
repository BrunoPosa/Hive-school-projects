#include "../../inc/Server.hpp"

void Server::cmdUser(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, username, mode, unused;
    
    // Read the first 4 parts (USER <username> 0 *), rest is realname
    iss >> command >> username >> mode >> unused;

    std::string realname;
    std::getline(iss, realname);

    // Trim leading space and optional colon
    if (!realname.empty() && realname[0] == ' ')
        realname = realname.substr(1);
    if (!realname.empty() && realname[0] == ':')
        realname = realname.substr(1);

    if (username.empty() || mode.empty() || unused.empty() || realname.empty()) {
        std::string errMsg = ERR_NEEDMOREPARAMS(command);
        ft_send(fd, errMsg);
        return;
    }

    if (clients_[fd].hasReceivedUser()) {
        std::string errMsg = ERR_ALREADYREGISTERED;
        ft_send(fd, errMsg);
        return;
    }

    // Simulate lack of Ident server by prefixing with '~'
    clients_[fd].setUser("~" + username);
    clients_[fd].setRealName(realname);
    clients_[fd].setUserReceived();

    // Registration completion usually happens only after both NICK and USER received
    if (clients_[fd].hasReceivedNick()) {
        std::string welcomeMsg = RPL_WELCOME(clients_[fd].getNick());
        ft_send(fd, welcomeMsg);
    }
}

