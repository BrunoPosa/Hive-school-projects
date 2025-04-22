#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using std::cout;
using std::endl;

int main (void) {
	//create a socket
	int	listening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listening == -1) {
		cout << "Can't create socket!" << endl;
		return -1;
	}
	//Bind the socket to an IP / port
	sockaddr_in	hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

	if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) {
		cout << "Can't bind to IP/Port!" << endl;
		return -2;
	}
	//Mark the socket for listening
	if (listen(listening, SOMAXCONN) == -1) {
		cout << "Can't listen!" << endl;
		return -3;
	}
	//Accept a call
	sockaddr_in	client;
	socklen_t	clientSize = sizeof(client);
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];

	int	clientSocket = accept(listening,
							(sockaddr*)&client,
							&clientSize);
	if (clientSocket == -1) {
		cout << "Problem with client connecting!" << endl;
		return -4;
	}
	//Close the listening socket
	close (listening);

	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr*)&client,
								sizeof(client), 
								host,
								NI_MAXHOST,
								svc,
								NI_MAXSERV,
								0);
	if (result) {
		cout << host << " connected on " << svc << endl;
	} else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on " << ntohs(client.sin_port) << endl;
	}
	//While receiving- display msg, echo msg
	char	buf[4096];
	while (true) {
		//Clear the buffer
		memset (buf, 0, 4096);
		//Wait for msg
		int	byteRecv = recv(clientSocket, buf, 4096, 0);
		if (byteRecv == -1) {
			cout << "There was a connection issue!" << endl;
			break;
		}
		if (byteRecv == 0) {
			cout << "The client disconnected!" << endl;
			break;
		}
		//Display msg
		cout << "aReceived: " << std::string(buf, 0, byteRecv) << endl;
		//Resend msg
		send (clientSocket, buf, byteRecv + 1, 0);
	}
	//Close socket
	close (clientSocket);



	return 0;
}