#include "PmergeMe.hpp"

using std::cout;
using std::endl;


size_t	PmergeMe::comparisons = 0;

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

	#ifdef COMPARISON_COUNT
		cout << "comparisons: " << PmergeMe::comparisons << endl;
	#endif
}

//returns std::vector<int>& ?
//sorts vector containing any type of elements
//ideally avoids moving elements until last moment (sorts indices/pointers)
template<typename T>
void PmergeMe::sorter(std::vector<T>& args) {

	std::size_t n = args.size();
	if (n <= 1) return;
	bool pairless = n % 2;
	T* extra;
	pairless ? extra = &args[n - 1] : extra = nullptr;
	cout << "extra:" << ((pairless) ? *extra : -1) << endl;

	std::vector<T>a;
	std::vector<std::pair<T, T>>b;//use reference T&?
	a.reserve(n / 2);
	b.reserve(n / 2 + pairless);

	for (std::size_t i = 0; i < n - pairless; i += 2) {
		std::pair<T, T> pair(args.at(i), args.at(i + 1));//rm .at, use forward?
		if (!isLLessThanR(pair.first, pair.second)) {
			std::swap(pair.first, pair.second);
		}
		a.emplace_back(pair.second);//bigger element in pair
		b.emplace_back(pair);
	}

	PmergeMe::sorter(a);
	cout << "a vector:" << endl;
	for (auto var : a) {
		cout << var << " ";
	}
	cout << endl << "b vector:" << endl;
	for (auto it : b) {
		cout << it.first << " ";//smaller
	}
	if (extra) {
		cout << *extra;
	}
	cout << endl;

}

//returns std::deque<int>& ?
template<typename T>
void PmergeMe::sorter(std::deque<T>& args) {

	// std::sort(args.begin(), args.end());
	cout << FMT_YELLOW << "deque sort placeholder.. " << FMT_CLEAR << endl;
	(void)args;
}

