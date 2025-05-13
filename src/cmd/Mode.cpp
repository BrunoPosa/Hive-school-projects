#include "../../inc/Server.hpp"

// Mode.cpp
void Server::cmdMode(int fd, const std::string& message) {
    std::istringstream iss(message);
    std::string command, target, modeStr;

    iss >> command >> target >> modeStr;

    std::clog << "Debug: Channel found channelname: " << target << std::endl;
    std::clog << "Debug: Channel found mode: " << modeStr << std::endl;

    if (target.empty() || modeStr.empty()) {
        ft_send(fd, ERR_NEEDMOREPARAMS);
        return;
    }

    // Handle user mode requests (skip for now)
    if (target == "*" || target[0] != '#') {
        std::clog << "Debug: Ignoring user mode command for now" << std::endl;
        return;
    }

    // Check if channel exists
    if (channels_.find(target) == channels_.end()) {
        ft_send(fd, ERR_NO_SUCH_CHANNEL(target));
        return;
    }

    // Process the mode string
    for (size_t i = 0; i < modeStr.size(); ++i) {
        char mode = modeStr[i];
        switch (mode) {
            case '+':
                std::cerr << "Debug: Adding" << std::endl;
                break;
            case '-':
                std::cerr << "Debug: Removing" << std::endl;
                break;
            default:
                ft_send(fd, ERR_UNKNOWNMODE(std::string(1, mode)));
                return;
        }
    }
}
