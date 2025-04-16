#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>
#include <stdexcept>

namespace irc {
    class Server; // Forward declaration of Server class
}

class Server {
public:
// setters
    void setPort(int port) { port_ = port; }
    void setPassword(const std::string& password) { password_ = password; }
    void setServerFd(int fd) { serverFd_ = fd; }
// getters
    int getPort() const { return port_; }
    const std::string& getPassword() const { return password_; }
    int getServerFd() const { return serverFd_; }
    void run(); // Placeholder for server run method
    void setupSocket(); // Placeholder for socket setup method
    void handleConnections(); // Placeholder for connection handling method

// constructor
    Server();// Default constructor
    Server(int port, const std::string& password); // Parameterized constructor
// destructor
    ~Server();
private:
    int port_;
    std::string password_;
    int serverFd_;
};
    int argCheck(int argc, char* argv[], Server& server); // Take Server reference as parameter
    bool isValidPort(const std::string& port);
    bool isValidPassword(const std::string& password);

#endif // IRC_HPP