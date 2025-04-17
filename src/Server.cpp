#include "../inc/irc.hpp"

// Default constructor
Server::Server() : port_(0), password_(""), serverFd_(-1) {
    // Initialize default values
}
// Parameterized constructor
Server::Server(const int port, const std::string& password) : port_(port), password_(password), serverFd_(-1) {
    // Initialize with provided values
}
// Destructor
Server::~Server() {
    // Cleanup resources if needed
    if (serverFd_ != -1) {
        close(serverFd_);
    }
}
void Server::run() {
    std::cout << "Starting server..." << std::endl; // Debug output
    setupServer(); // Set up the server
    mainLoop(); // Start the main loop
}
void Server::setupServer() {
    serverFd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd_ < 0) {
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
    // Set socket to non-blocking
    int flags = fcntl(serverFd_, F_GETFL, 0);
    fcntl(serverFd_, F_SETFL, flags | O_NONBLOCK);

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port_);

    if (bind(serverFd_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(serverFd_);
        throw std::runtime_error("Failed to bind socket: " + std::string(strerror(errno)));
    }

    if (listen(serverFd_, 5) < 0) {
        close(serverFd_);
        throw std::runtime_error("Failed to listen on socket: " + std::string(strerror(errno)));
    }

    // Initialize pollFds_ with server socket
    pollFds_.clear();
    pollFds_.push_back((pollfd){serverFd_, POLLIN, 0});
    std::cout << "Server setup complete on port " << port_ << std::endl;
}
void Server::mainLoop() {
    std::cout << "Entering main loop with " << pollFds_.size() << " file descriptors" << std::endl;
    
    while (true) {
        
        int ready = poll(&pollFds_[0], pollFds_.size(), -1);
        if (ready < 0) {
            std::cerr << "poll() error: " << strerror(errno) << std::endl;
            if (errno == EINTR) continue;
            throw std::runtime_error("poll() failed");
        }
        else if (ready == 0) {
            std::cout << "poll() timeout (shouldn't happen with infinite timeout)" << std::endl;
            continue;
        }
        
        // Check all file descriptors, not just server socket
        for (size_t i = 0; i < pollFds_.size(); i++) {
            if (pollFds_[i].revents & POLLIN) {
                if (i == 0) { // Server socket
                    acceptNewConnection();
                }
                else { // Client socket
                    handleClient(i);
                }
            }
            if (pollFds_[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                std::cerr << "Error condition on fd " << pollFds_[i].fd << std::endl;
                close(pollFds_[i].fd);
                pollFds_.erase(pollFds_.begin() + i);
                i--; // Adjust index after erase
            }
        }
    }
}
void Server::acceptNewConnection() {
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientFd = accept(serverFd_, (struct sockaddr*)&clientAddr, &clientAddrLen);
    
    if (clientFd < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            // No pending connections available right now
            std::cout << "accept() would block" << std::endl;
        } else {
            std::cerr << "accept() error: " << strerror(errno) << std::endl;
        }
        return;
    }

    // Set client socket to non-blocking
    int flags = fcntl(clientFd, F_GETFL, 0);
    fcntl(clientFd, F_SETFL, flags | O_NONBLOCK);

    std::cout << "Accepted new connection from " 
              << inet_ntoa(clientAddr.sin_addr) << ":"
              << ntohs(clientAddr.sin_port) 
              << " (FD: " << clientFd << ")" << std::endl;

    pollFds_.push_back((pollfd){clientFd, POLLIN | POLLOUT, 0});
    
    // Send welcome message
    std::string welcome = "Welcome to ft_irc!\r\n";
    if (send(clientFd, welcome.c_str(), welcome.size(), 0) < 0) {
        std::cerr << "send() error: " << strerror(errno) << std::endl;
    }
}
void Server::handleClient(size_t index) {
    char buffer[1024];
    ssize_t bytesRead = recv(pollFds_[index].fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytesRead <= 0) {
        // Get client info before closing
        struct sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);
        getpeername(pollFds_[index].fd, (struct sockaddr*)&clientAddr, &addrLen);
        
        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIp, INET_ADDRSTRLEN);
        
        if (bytesRead == 0) {
            std::cout << "Client disconnected: " 
                      << clientIp << " (FD: " << pollFds_[index].fd << ")" << std::endl;
        } else {
            std::cerr << "Error with client " << clientIp 
                      << " (FD: " << pollFds_[index].fd << "): " 
                      << strerror(errno) << std::endl;
        }
        
        close(pollFds_[index].fd);
        pollFds_.erase(pollFds_.begin() + index);
        return;
    }

    buffer[bytesRead] = '\0';
    
    // Get client info
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    getpeername(pollFds_[index].fd, (struct sockaddr*)&clientAddr, &addrLen);
    char clientIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIp, INET_ADDRSTRLEN);
    
    std::string message(buffer);
    std::cout << "RAW from " << clientIp << " (FD " << pollFds_[index].fd << "): " 
              << message << std::endl;

    // Handle NICK command
    if (message.find("NICK ") == 0) {  // Check if message starts with "NICK "
        size_t end = message.find("\r\n");
        if (end != std::string::npos) {
            std::string newNick = message.substr(5, end - 5);  // Extract nickname
            // Basic validation
            if (newNick.empty() || newNick.find(' ') != std::string::npos) {
                std::string error = ":localhost 432 * " + newNick + " :Erroneous nickname\r\n";
                send(pollFds_[index].fd, error.c_str(), error.size(), 0);
            } else {
                // Store nickname (you'll need to add client tracking)
                std::cout << "Client FD " << pollFds_[index].fd 
                          << " changed nickname to: " << newNick << std::endl;
                
                // Send success response
                std::string reply = ":localhost 001 " + newNick + " :Welcome to the IRC server\r\n";
                send(pollFds_[index].fd, reply.c_str(), reply.size(), 0);
            }
        }
    }
    // Add other command handlers here later (USER, JOIN, etc.)
}
