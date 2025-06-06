#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

std::string getPublicFacingIP() {
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) return "Could not create socket";

	sockaddr_in remoteAddr{};
	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_port = htons(80);
	inet_pton(AF_INET, "8.8.8.8", &remoteAddr.sin_addr);  // doesn't actually connect

	if (connect(sock, (sockaddr*)&remoteAddr, sizeof(remoteAddr)) == -1) {
		close(sock);
		return "connect() failed";
	}

	sockaddr_in localAddr{};
	socklen_t len = sizeof(localAddr);
	if (getsockname(sock, (sockaddr*)&localAddr, &len) == -1) {
		close(sock);
		return "getsockname() failed";
	}

	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &localAddr.sin_addr, ip, sizeof(ip));
	close(sock);
	return std::string(ip);
}

#include <netdb.h>

std::string resolvePTRRecord(std::string ip) {
	sockaddr_in sa{};
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &sa.sin_addr);

	char host[NI_MAXHOST];
	int err = getnameinfo((sockaddr*)&sa, sizeof(sa), host, sizeof(host), nullptr, 0, NI_NAMEREQD);
	if (err != 0)
		return std::string("Reverse DNS failed: ") + gai_strerror(err);
	return std::string(host);
}

int main (void){

std::string a = "hello, this is long and on the heap dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
std::string b = std::move(a);
std::cout << a << "|" << b << std::endl;

	std::string ip = getPublicFacingIP();
	std::cout << "Public IP: " << ip << std::endl;
	std::cout << "Reverse DNS (FQDN): " << resolvePTRRecord(ip) << std::endl;

	return 0;
}