#include <netdb.h>
#include <cstring>
#include <iostream>
#include <iostream>
#include <string>
#include <netdb.h>

#include <unistd.h>
#include <cstring>
#include <string>
#include <string_view>
#include <iostream>
#include <arpa/inet.h> //inet_ntop
#include <netinet/in.h>
#include <system_error>
#include <sys/socket.h> //SOMAXCONN, listen()
#include <cassert>
#include <utility>//std::exchange
#include <netdb.h> //resolving host

#include <limits.h>
void print_my_ip() {
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, HOST_NAME_MAX) != 0) {
        perror("gethostname");
        return;
    }

    std::cout << "Hostname: " << hostname << std::endl;

    addrinfo hints = {}, *res;
    hints.ai_family = AF_INET; // IPv4 only
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, nullptr, &hints, &res) != 0) {
        perror("getaddrinfo");
        return;
    }

    for (addrinfo* p = res; p != nullptr; p = p->ai_next) {
        char ipStr[INET_ADDRSTRLEN];
        sockaddr_in* ipv4 = reinterpret_cast<sockaddr_in*>(p->ai_addr);
        inet_ntop(AF_INET, &(ipv4->sin_addr), ipStr, INET_ADDRSTRLEN);
        std::cout << "Resolved IP: " << ipStr << std::endl;
    }

    freeaddrinfo(res);
}


int main(void) {
print_my_ip();


return 0;}
