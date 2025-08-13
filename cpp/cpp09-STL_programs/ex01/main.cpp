#include "RPN.hpp"

using std::cout;
using std::endl;

int main (int ac, char** av) {

	if (ac != 2) {
		cout << RPN_YELLOW << "usage: ./RPN \"7 7 * -7 -\"" << RPN_CLEAR << endl;
		return 1;
	}

	try {

		RPN a(av[1]);

	} catch (std::exception& e) {
		cout << RPN_YELLOW << e.what() << RPN_CLEAR << endl;
		return 2;
	} catch (...) {
		cout << RPN_RED << "stray exception! catch & release" << endl;
		throw;
	}

	return 0;
}