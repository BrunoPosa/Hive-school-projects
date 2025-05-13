#include "../../inc/Server.hpp"

void Server::cmdPing(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, serverName;
    iss >> command >> serverName;

    if (serverName.empty()) {
        std::string errMsg = ERR_NO_PING_TARGET;
        ft_send(fd, errMsg);
        return;
    }

    // Send PONG response back to the client
    std::string pongResponse = ":localhost PONG localhost :" + serverName + "\r\n";
    send(fd, pongResponse.c_str(), pongResponse.size(), 0);
}