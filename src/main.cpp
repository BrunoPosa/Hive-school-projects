#include "../inc/Server.hpp"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	try {
		Config  config(argv[1], argv[2]);
		Server	server(std::move(config));

		server.run();

		std::cout << "Closing server.." << std::endl;

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 1;
}
