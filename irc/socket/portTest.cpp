#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <system_error>
#include <unistd.h>

int main() {
    int fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0) {
        throw std::system_error(errno, std::generic_category(), "socket() failed");
    }

    // Bind to port 0 (OS picks one)
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(0);  // Let OS choose

    if (::bind(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd_);
        throw std::system_error(errno, std::generic_category(), "bind() failed");
    }

    // Get the assigned port
    sockaddr_in assigned_addr{};
    socklen_t len = sizeof(assigned_addr);
    if (::getsockname(fd_, reinterpret_cast<sockaddr*>(&assigned_addr), &len) < 0) {
        ::close(fd_);
        throw std::system_error(errno, std::generic_category(), "getsockname() failed");
    }

    uint16_t assigned_port = ntohs(assigned_addr.sin_port);
    std::cout << "OS-assigned port: " << assigned_port << std::endl;

    ::close(fd_);
    return 0;
}