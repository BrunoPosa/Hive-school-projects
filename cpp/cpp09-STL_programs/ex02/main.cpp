#include "PmergeMe.hpp"

using std::cout;
using std::cerr;
using std::endl;

int main (int ac, char **av) {

	if (ac < 2 || PmergeMe::validateStr(ac, av) == false) {
		cerr << FMT_YELLOW << "Usage: ./PmergeMe <positive int sequence>" << FMT_CLEAR << endl;
		return 1;
	}

	try {
		std::deque<int>		dq;
		std::vector<int>	vec;
		vec.reserve(ac);
		
		//init containers with given values
		cout << "Before:";
		for (int i = 1; i < ac; i++) {
			int num = std::stoi(av[i]);
			cout << " " << num;
			dq.push_back(num);
			vec.push_back(num);
		}
		cout << endl;

		//sort and print results
		cout << " After: ";
		PmergeMe::runComparison(vec, dq);

	} catch (std::exception& e) {
		cerr << FMT_YELLOW << "\nException! " << e.what() << FMT_CLEAR << endl;
		return 2;
	} catch (...) {
		cerr << FMT_RED << "\nstray exception! catch & release" << endl;
		throw;
	}

	return 0;	
}