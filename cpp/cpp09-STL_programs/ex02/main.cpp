#include "PmergeMe.hpp"

using std::cout;
using std::cerr;
using std::endl;

// #define DEQUE

int main (int ac, char **av) {
	
	if (ac < 2 || PmergeMe<std::vector<int>>::validateStr(ac, av) == false) {
		cout << FMT_YELLOW << "Usage: ./PmergeMe <positive int sequence>" << FMT_CLEAR << endl;
		return 1;
	}

	try {

		#ifdef DEQUE
			std::deque<int>	dq;
		#else
			std::vector<int> vec;
			vec.reserve(ac);
		#endif

		cout << "Before: " << endl;
		for (int i = 1; i < ac; i++) {	
			cout << av[i] << " ";
			#ifdef DEQUE
				dq.push_back(std::stoi(av[i]));
			#else
				vec.push_back(std::stoi(av[i]));
			#endif
		}
		cout << endl;

		#ifdef DEQUE
			PmergeMe<std::deque<int>>::sort(dq);
		#else
			PmergeMe<std::vector<int>>::sort(vec);
		#endif


	} catch (std::exception& e) {
		cerr << FMT_YELLOW << "\nException! " << e.what() << FMT_CLEAR << endl;
		return 2;
	} catch (...) {
		cerr << FMT_RED << "\nstray exception! catch & release" << endl;
		throw;
	}

	return 0;	
}