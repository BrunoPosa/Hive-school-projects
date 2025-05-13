#include "../inc/Server.hpp"

//processCommand function to handle incoming commands from clients
void Server::processCommand(int fd, const std::string& message)
{
    std::istringstream iss(message);
    std::vector<std::string> tokens;
    std::string token;

    std::string command;
    std::cerr << "message: " << message << std::endl;
    if (iss)
        iss >> command;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    if (token.empty()) {
        std::cerr << "Empty command received from FD: " << fd << std::endl;
        return;
    }
    std::unordered_map<std::string, int> cmdMap = {
        {"NICK", 1},
        {"USER", 2},
        {"JOIN", 3},
        {"MODE", 4},
        {"PING", 5},
        {"KICK", 6},
        {"TOPIC", 7},
        {"PRIVMSG", 8},
        {"INVITE",9},
        {"QUIT", 10}
    };
    
    auto it = cmdMap.find(command);
    // Check if the command exists in the map
    if (it != cmdMap.end()) { 
        switch (it->second) {
            case 1:
                std::cerr << "NICK command received from FD: " << fd << std::endl;
                cmdNick(fd, message);
                break;
            case 2:
                std::cerr << "USER command received from FD: " << fd << std::endl;
                cmdUser(fd, message);
                break;
            case 3:
                std::cerr << "JOIN command received from FD: " << fd << std::endl;
                cmdJoin(fd, message);
                break;
            case 4:
                std::cerr << "MODE command received from FD: " << fd << std::endl;
                cmdMode(fd, message);
                break;
            case 5:
                std::cerr << "PING command received from FD: " << fd << std::endl;
                cmdPing(fd, message);
                break;
            case 6:
                std::cerr << "KICK command received from FD: " << fd << std::endl;
                cmdKick(fd, tokens);
                break;
            case 7:
                std::cerr << "TOPIC command received from FD: " << fd << std::endl;
                cmdTopic(fd, message);
                break;
            case 8:
                std::cerr << "PRIVMSG command received from FD: " << fd << std::endl;
                cmdPrivMsg(fd, message);
                break;
            case 9:
                // Handle INVITE command
                break;
            case 10:
                // Handle QUIT command
                break;
            default:
                std::cerr << "Unknown command: " << command << std::endl;
        }
    } else {
        std::cerr << "Unknown command received from FD: " << fd << " - " << command << std::endl;
    }
}
