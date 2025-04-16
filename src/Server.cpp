#include "irc.hpp"

// Default constructor
Server::Server() : port_(0), password_(""), serverFd_(-1) {
    // Initialize default values
}
// Parameterized constructor
Server::Server(int port, const std::string& password) : port_(port), password_(password), serverFd_(-1) {
    // Initialize with provided values
}
// Destructor
Server::~Server() {
    // Cleanup resources if needed
    if (serverFd_ != -1) {
        close(serverFd_);
    }
}
