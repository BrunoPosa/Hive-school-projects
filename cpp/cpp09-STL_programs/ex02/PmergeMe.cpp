#include "PmergeMe.hpp"

using std::cout;
using std::endl;

//is it faster to process passing a single argument of space-separated ints? or as many args
bool PmergeMe::validateStr(int ac, char **args) {
	for (int i = 1; i < ac; i++) {
		int j = 0;
		if (args[i][0] == '\0') {
			return false;
		}

		while (args[i][j]) {
			if (std::isdigit(args[i][j]) == false) {
				return false;
			}
			j++;
		}
	}
	return true;
}

void	PmergeMe::runComparison(std::vector<int>& vec, std::deque<int>& dq) {
	auto durVec = PmergeMe::measureSorting(vec);
	auto durDq = PmergeMe::measureSorting(dq);

	if (std::equal(vec.begin(), vec.end(), dq.begin(), dq.end())) {
		PmergeMe::printValues(vec);
	} else {
		cout << " sorting failed!";
	}

	cout << "Time to process a range of " << vec.size()
		<< " elements with std::vector<int> : "
    	<< std::fixed << std::setprecision(3) << durVec << " µs" << endl;

	cout << "Time to process a range of " << dq.size()
		<< " elements with std::deque<int>  : "
    	<< std::fixed << std::setprecision(3) << durDq << " µs" << endl;

	#ifdef STEPCOUNT
		cout << "step count: in progress" << endl;
	#endif
}

//returns std::vector<int>& ?
void PmergeMe::sort(std::vector<int>& args) {
	std::sort(args.begin(), args.end());
}

//returns std::deque<int>& ?
void PmergeMe::sort(std::deque<int>& args) {
	std::sort(args.begin(), args.end());
}
