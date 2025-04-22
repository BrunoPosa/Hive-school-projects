#include "../../inc/irc.hpp"

void Server::cmdNick(int fd, const std::string& message) {
    size_t end = message.find("\r\n");
    if (end != std::string::npos) {
        std::string newNick = message.substr(5, end - 5);
        
        // Validate nickname
        if (newNick.empty() || newNick.find(' ') != std::string::npos) {
            send(fd, ":localhost 432 * :Erroneous nickname\r\n", 38, 0);
            return;
        }
        
        // Store nickname
        clients_[fd].nick = newNick;
        checkRegistration(fd);
    }
}