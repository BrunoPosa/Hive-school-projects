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

void	PmergeMe::measuredSort(std::vector<int>& vec, std::deque<int>& dq) {
	auto startVec = std::chrono::high_resolution_clock::now();
    PmergeMe::sort(vec);
    auto endVec = std::chrono::high_resolution_clock::now();
	
	auto startDq = std::chrono::high_resolution_clock::now();
    PmergeMe::sort(dq);
    auto endDq = std::chrono::high_resolution_clock::now();

	(std::equal(vec.begin(), vec.end(), dq.begin(), dq.end()))
		?	PmergeMe::printValues(vec)
		:	cout << "containers different!";

	cout << "Time to process a range of " << vec.size() << " elements with std::vector<int> : "
    	<< std::chrono::duration_cast<std::chrono::microseconds>(endVec - startVec).count() << endl;

	PmergeMe::printValues(dq);
	cout << "Time to process a range of " << dq.size() << " elements with std::deque<int> : "
    	<< std::chrono::duration_cast<std::chrono::microseconds>(endDq - startDq).count() << endl;
}

//returns std::vector<int>& ?
void PmergeMe::sort(std::vector<int>& args) {
	std::sort(args.begin(), args.end());
}

//returns std::deque<int>& ?
void PmergeMe::sort(std::deque<int>& args) {
	std::sort(args.begin(), args.end());
}
