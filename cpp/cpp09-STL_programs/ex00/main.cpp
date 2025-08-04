#include "BitcoinExchange.hpp"

#include <iostream>
#include <string>
#include <exception>

using std::cout;
using std::endl;
using std::string;

namespace {
	void printUsage() {
		cout << BTC_YELLOW << "usage: ./btc <filename>" << BTC_CLEAR << endl;
	}	
}
/*
	-av can be ARG_MAX which may be INT_MAX, so we may not want to alloc for the av
*/
int main (int ac, char** av) {

	if (ac != 2) {
		printUsage();
		return 1;
	}

	try {

		std::string str(av[1]);

		BitcoinExchange a(av[1]);
		// BitcoinExchange b(str);

	} catch (std::exception& e) {
		cout << BTC_RED << e.what() << BTC_CLEAR << endl;
		return 2;
	} catch (...) {
		cout << BTC_RED << "other exception!" << endl;
		throw;
	}

	return 0;
}