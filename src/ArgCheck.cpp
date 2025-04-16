#include "../inc/irc.hpp"

int argCheck(int argc, char* argv[], Server& server) {  // Take Server reference as parameter
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
        return 1;
    }
    //check port
    if (!isValidPort(argv[1])) {
        std::cerr << "Invalid port number. Port must be between 1024 and 65535.\n";
        return 1;
    }
    server.setPort(std::stoi(argv[1])); // Set port in server object
    //check server password
    if (!isValidPassword(argv[2])) {
        std::cerr << "Invalid password. Password must be alphanumeric and cannot be empty.\n";
        return 1;
    }
    server.setPassword(argv[2]); // Set password in server object
    return 0; // Return 0 if everything is fine
}

bool isValidPort( const std::string& portStr) {
    if (portStr[0] == '0') {
        return false; // Port cannot start with '0'
    }
    if (portStr.find_first_not_of("0123456789") != std::string::npos) {
        return false; // Not a valid integer
    }    
    try {
        int port = std::stoi(portStr); // Convert string to int
        return (port >= 1024 && port <= 65535); // Check if port is in valid range
    } catch (const std::invalid_argument& e) {
        return false; // Not a valid integer
    } catch (const std::out_of_range& e) {
        return false; // Out of range for int
    } catch (...) {
        return false; // Catch any other exceptions
    }
}
bool isValidPassword(const std::string& password) {
    // Check if password is empty or contains invalid characters
    if (password.empty() || password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos) {
        return false;
    }
    return true;
}