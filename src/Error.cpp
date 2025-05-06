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


