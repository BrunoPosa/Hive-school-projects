#include "../../inc/irc.hpp"

void Server::cmdJoin(int fd, const std::string& message) {
    std::cout << "received JOIN command " << message << fd << std::endl;
}