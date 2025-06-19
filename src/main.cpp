#include "../inc/Server.hpp"

namespace {

	void	sigShutdown(int signum) {
		std::cerr << YELLOWIRC << "\nSignal caught: " << strsignal(signum) << RESETIRC << std::endl;
		if (g_servPtr) {
			g_servPtr->gracefulShutdown();
		}
	}
}

int main(int argc, char* argv[])
{
	if (signal(SIGTERM, sigShutdown) == SIG_ERR
	|| signal(SIGINT, sigShutdown) == SIG_ERR
	|| signal(SIGQUIT, sigShutdown) == SIG_ERR
	|| signal(SIGHUP, sigShutdown) == SIG_ERR
	|| signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		std::cerr << "signal() setup failed" << std::endl;
		return 1;
	}
	if (argc != 3) {
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return 2;
	}
	try {
		Config	config(argv[1], argv[2]);
		Server	ircserver(std::move(config));//config unreachable after this

		g_servPtr = &ircserver;

		ircserver.run();

	} catch (const std::exception& e) {
		std::cerr << REDIRC << "Exception caught in main!" << RESETIRC << e.what() << std::endl;
		return 3;
	} catch (...) {
		std::cerr << REDIRC << "... exception caught in main!" << RESETIRC << std::endl;
		throw;
	}
	return 0;
}
