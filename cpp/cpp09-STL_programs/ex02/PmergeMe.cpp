#include "PmergeMe.hpp"

using std::cout;
using std::endl;

size_t	PmergeMe::comparisons = 0;
size_t	PmergeMe::size = 0;

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

std::vector<size_t> PmergeMe::generateJacobsthalOrder(size_t n) {
    std::vector<std::size_t> order;

	std::size_t prev = 0;
	std::size_t curr = 1;

	while (curr < n) {
		if (order.empty() || order.back() != curr) {
			order.push_back(curr);
		}
		std::size_t gap = curr - 1;
		while (gap > prev) {
			order.push_back(gap);
			gap--;
		}
		std::size_t next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	while (n != prev) {
		order.push_back(n--);
	}
	#ifdef TRACE
		cout<< FMT_GREEN << "order:" ;
		for (auto& it: order) cout << it << " ";
		cout << FMT_CLEAR << endl;
	#endif
	return order;
}
