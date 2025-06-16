// bible_flooder
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6667
#define SLEEP_US 15 // microseconds delay between sends

int main() {
	//connect
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		return 1;
	}

	struct sockaddr_in serv_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(SERVER_PORT)
	};
	inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect");
		return 1;
	}

	printf("Connected to IRC server at %s:%d\n", SERVER_IP, SERVER_PORT);


	//auth
	std::string authMsg("CAP LS\r\nPASS 4242\r\nNICK booooop\r\nUSER booooop booooop localhost :Brunuiu\r\n");
	if (send(sock, authMsg.c_str(), authMsg.length(), 0) < 0) {
		perror("send");
		return 1;
	}
	usleep(500000);
	std::string joinMsg("JOIN #bible\r\nPRIVMSG #bible :h00i here comes the Bible\r\n");
	if (send(sock, joinMsg.c_str(), joinMsg.length(), 0) < 0) {
		perror("send");
		return 1;
	}
	usleep(500000);

	

	//read and send lines from file
	FILE *fp = fopen("bible.txt", "r");
	if (!fp) {
		perror("fopen");
		return 1;
	}

	char line[512];
	while (fgets(line, sizeof(line), fp)) {
		// Format as IRC message
		char message[1024];
		snprintf(message, sizeof(message), "PRIVMSG #bible :%s\r\n", line);

		ssize_t sent = send(sock, message, strlen(message), 0);
		if (sent < 0) {
			perror("send");
			break;
		}

		usleep(SLEEP_US); // Optional throttle (adjust or remove)
	}

	fclose(fp);
	close(sock);
	return 0;
}
