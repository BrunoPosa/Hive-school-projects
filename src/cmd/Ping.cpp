#include "../../inc/Server.hpp"

void Server::cmdPing(int fd, const t_data data) {
    std::istringstream iss(data.fullMsg);
    std::string command, serverName;
    iss >> command >> serverName;

    if (serverName.empty()) {
        std::string errMsg = ERR_NO_PING_TARGET;
        ft_send(fd, errMsg);
        return;
    }

    // Send PONG response back to the client
    std::string pongResponse = ":localhost PONG localhost :" + serverName + "\r\n";
    ft_send(fd, pongResponse.c_str());
}