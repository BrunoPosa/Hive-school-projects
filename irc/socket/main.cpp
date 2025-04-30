
#include <arpa/inet.h>
#include "Socket.hpp"
#include <cassert>
#include <chrono>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

// Test 1: Basic construction
void test_constructor() {
	Socket s;
	int fd = s.getFd();
	std::cout << "[test_constructor] Created socket with fd = " << fd << "\n";
	assert(fd >= 0);
}

// Test 2: Move constructor
void test_move_constructor() {
	Socket s;
	int origFD = s.getFd();
	// Move s into moved
	Socket moved = std::move(s);
	std::cout << "[test_move_constructor] Moved socket: original fd now = "
			  << s.getFd() << ", moved fd = " << moved.getFd() << "\n";
	assert(s.getFd() == -1);
	assert(moved.getFd() == origFD);
}

// Test 3: Listener, accept, send, and receive.
// This test creates a listener socket bound to an ephemeral port.
// A client thread is spawned that connects to the listener on localhost.
// Once connected, the server sends a message to the client and then
// the client replies back. (Since our Socket is non‑blocking, we use
// short retry loops to wait for accept() and for receiving data.)
void test_listener_accept_send_receive() {
    try {
        // Create a listener socket, bind it, and start listening.
        Socket listener;
        listener.makeListener(0); // Port 0 = OS assigns an ephemeral port

        // Retrieve the actual port assigned using getsockname.
        sockaddr_in sin{};
        socklen_t addrLen = sizeof(sin);
        assert(getsockname(listener.getFd(), reinterpret_cast<sockaddr*>(&sin), &addrLen) == 0);
        uint16_t port = ntohs(sin.sin_port);
        std::cout << "[test_listener_accept_send_receive] Listener bound on port: " << port << "\n";

        // Spawn a client thread that connects to the listener.
        std::thread client_thread([port]() {
            int client_fd = ::socket(AF_INET, SOCK_STREAM, 0);
            if (client_fd < 0) {
                perror("client socket() failed");
                std::exit(1);
            }
            sockaddr_in serv{};
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
            if (::inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr) != 1) {
                perror("inet_pton failed");
                std::exit(1);
            }

            // Connect to the server.
            int res = ::connect(client_fd, reinterpret_cast<sockaddr*>(&serv), sizeof(serv));
            if (res < 0) {
                perror("client connect() failed");
                std::exit(1);
            }

            // Wait for server to send its message.
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            // Receive message from server.
            char buffer[256] = {0};
            ssize_t n = ::recv(client_fd, buffer, sizeof(buffer), 0);
            if (n < 0) {
                perror("client recv() failed");
                std::exit(1);
            }
            std::string serverMsg(buffer, static_cast<size_t>(n));
            std::cout << "[client thread] Received from server: \"" << serverMsg << "\"\n";

            // Send a response to the server.
            const char* response = "Hello from client";
            n = ::send(client_fd, response, strlen(response), 0);
            if (n < 0) {
                perror("client send() failed");
                std::exit(1);
            }
            ::close(client_fd);
        });

        // Retry for a short period because Socket is non-blocking.
        Socket acceptedSocket;
        const int maxRetries = 50;
        int retries = maxRetries;
        bool accepted = false;
        while (retries-- > 0) {
            accepted = listener.accept(acceptedSocket);
            if (accepted) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        assert(accepted);
        std::cout << "[test_listener_accept_send_receive] Accepted connection\n";

        // Test sending message from server to client.
        std::string serverMessage = "Hello from server";
        ssize_t sent = acceptedSocket.send(serverMessage);
        std::cout << "[test_listener_accept_send_receive] Server sent " << sent
                  << " bytes to client.\n";
        assert(sent == static_cast<ssize_t>(serverMessage.size()));

        // Wait and receive response from the client.
        std::string clientResponse;
        ssize_t received = 0;
        for (int i = 0; i < 10; i++) {
            received = acceptedSocket.receive(clientResponse);
            if (received > 0)
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "[test_listener_accept_send_receive] Server received " << received
                  << " bytes: \"" << clientResponse << "\"\n";
        assert(received > 0);
        assert(clientResponse == "Hello from client");

        client_thread.join();
        std::cout << "[test_listener_accept_send_receive] Listener/accept/send/receive test passed.\n";
    } catch (const std::exception& e) {
        std::cerr << "[test_listener_accept_send_receive] Exception: " << e.what() << "\n";
        assert(false);
    }
}



void test_move_assignment() {
	std::cout << "[test_move_assignment] Starting move assignment test...\n";

	// Create a Socket instance s1 using the default constructor.
	Socket s1;
	int s1_fd = s1.getFd();
	std::cout << "[test_move_assignment] s1 created with fd: " << s1_fd << "\n";

	// Create a second Socket instance s2.
	Socket s2;
	int s2_fd = s2.getFd();
	std::cout << "[test_move_assignment] s2 created with fd: " << s2_fd << "\n";

	// Use move-assignment to move s1 into s2.
	// This will first close the existing s2 socket, then assign s1's socket to s2.
	s2 = std::move(s1);

	// After the move, s1 should be in a "moved-from" state (fd == -1) and s2 should own s1's original descriptor.
	std::cout << "[test_move_assignment] After move assignment:\n";
	std::cout << "  s1 fd: " << s1.getFd() << " (expected -1)\n";
	std::cout << "  s2 fd: " << s2.getFd() << " (expected " << s1_fd << ")\n";

	assert(s1.getFd() == -1);
	assert(s2.getFd() == s1_fd);

	std::cout << "[test_move_assignment] Move assignment test passed.\n";
}


int main() {

	test_constructor();
	test_move_constructor();
	test_listener_accept_send_receive();
	test_move_assignment();

	return 0;
}
