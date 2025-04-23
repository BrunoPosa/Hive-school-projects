#include "../inc/irc.hpp"

// void Server::handleClientError(int errorCode, size_t index) {
//     struct sockaddr_in clientAddr;
//     socklen_t addrLen = sizeof(clientAddr);
//     getpeername(pollFds_[index].fd, (struct sockaddr*)&clientAddr, &addrLen);

//     char clientIp[INET_ADDRSTRLEN];
//     inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIp, INET_ADDRSTRLEN);

//     int fd = pollFds_[index].fd;

//     if (errorCode == 0) {
//         std::cout << "Client disconnected: " << clientIp << " (FD: " << fd << ")\n";
//     } else {
//         std::cerr << "Error with client " << clientIp 
//                   << " (FD: " << fd << "): " << strerror(errno) << "\n";
//     }

//     close(fd);
//     pollFds_.erase(pollFds_.begin() + index);
//     clients_.erase(fd);
// }

void Server::handleClientError(int errorCode, size_t index) {
    int fd = pollFds_[index].fd;
    
    // Get client info before cleanup
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    if (getpeername(fd, (struct sockaddr*)&clientAddr, &addrLen) < 0) {
        std::cerr << "getpeername error: " << strerror(errno) << "\n";
    }

    char clientIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIp, INET_ADDRSTRLEN);

    if (errorCode == 0) {
        std::cout << "Client disconnected: " << clientIp << " (FD: " << fd << ")\n";
    } else {
        std::cerr << "Error with client " << clientIp 
                  << " (FD: " << fd << "): " << strerror(errno) << "\n";
    }

    // Remove client from all channels
    for (std::set<std::string>::iterator it = clients_[fd].joinedChannels.begin();
         it != clients_[fd].joinedChannels.end(); ++it) {
        channels_[*it].broadcast(fd, clients_[fd].nick + " has quit", clients_[fd].nick);
    }

    // Clean up resources
    close(fd);
    pollFds_.erase(pollFds_.begin() + index);
    clients_.erase(fd);
}