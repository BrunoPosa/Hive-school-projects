
#include "Socket.hpp"
#include "IrcServer.hpp"
// #include <filesystem>
// #include <string_view>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <locale>
#include <cassert>

using std::string;
using std::cerr;
using std::cout;
using std::endl;

int main(int ac, char **av) {
	try {
		Socket  a;
		assert(a.getFd() == 5);
		(void)a;

		if (ac != 3) {
			cerr << "USAGE: ./ircserv <port> <password>" << endl;
			return -1;
		}

		return 0;

	} catch (const std::system_error& e) {
		cerr << YELLOWIRC << e.what() << ": " << e.code().message() << RESETCOLORIRC << endl;
	} catch (std::exception& e) {
		cerr << REDIRC << e.what() << RESETCOLORIRC << endl;
	}
	return -1;
}
