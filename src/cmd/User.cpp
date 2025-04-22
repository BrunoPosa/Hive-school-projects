#include "../../inc/irc.hpp"

void Server::cmdUser(int fd, const std::string& message) {
    std::cerr << "cmdUser called with message: " << message << std::endl; // Debug output
    size_t end = message.find("\r\n");
    if (end != std::string::npos) {
        clients_[fd].user = message.substr(5);
        std::cout << "User set to: " << clients_[fd].user << std::endl;
        checkRegistration(fd);
        clients_[fd].nameChanged = true; // Set nameChanged to true after USER command
    }
}
