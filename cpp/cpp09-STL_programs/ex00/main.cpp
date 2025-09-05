#include "BitcoinExchange.hpp"
#include <vector>

namespace {
	void printUsage() {
		cout << BTC_YELLOW << "usage: ./btc <filename>\n" << BTC_CLEAR
			<< "inside your file, the allowed syntax is:\n"
			<< BTC_YELLOW << "	<date> | <amount>\n" << BTC_CLEAR
			<< "*date must be YYYY-MM-DD, and amount between 0 and 1000.0\n"
			<< "*the 1st line of the file is the headline, e.g. 'date | value'" << endl;
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

		// std::string str(av[1]);

		BitcoinExchange a(av[1]);
		// BitcoinExchange b(str);

	} catch (std::exception& e) {
		cout << BTC_RED << e.what() << BTC_CLEAR << endl;
		return 2;
	} catch (...) {
		cout << BTC_RED << "stray exception! catch & release" << endl;
		throw;
	}

	return 0;
}