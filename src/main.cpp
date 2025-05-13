#include "../inc/Server.hpp"
//irc server
// ./irc <port> <password>
int main(int argc, char* argv[]) {
	if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
        return 1;
    }
    try {
    Config  config(argv[1], argv[2]);
	Server server(std::move(config)); // Create a Server object

	server.run();
	//print server information
	std::cout << "Server Port: " << server.getPort() << std::endl;
	}catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
