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

// size_t PmergeMe::jacobsthal(size_t n) {
//     if (n == 0) return 0;
//     if (n == 1) return 1;
//     return jacobsthal(n-1) + 2*jacobsthal(n-2);
// }

std::vector<size_t> PmergeMe::generateJacobsthalOrder(size_t size) {
    std::vector<std::size_t> order;
        std::size_t j_prev = 0;
        std::size_t j_curr = 1;
        while (j_curr <= size) {
            // push unique values only
            if (order.empty() || order.back() != j_curr) order.push_back(j_curr);
            std::size_t next = j_curr + 2 * j_prev;
            j_prev = j_curr;
            j_curr = next;
        }

        // Append missing indices in descending order safely
        for (std::size_t k = size; k >= 1; --k) {
            if (std::find(order.begin(), order.end(), k) == order.end())
                order.push_back(k);
            if (k == 1) break; // prevent underflow (size_t is unsigned)
        }

        return order;
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
	b.reserve(n / 2);

	for (std::size_t i = 0; i < n - pairless; i += 2) {
		std::pair<T, T> pair(args.at(i), args.at(i + 1));//rm .at, use forward?
		if (!isLLessThanR(pair.first, pair.second)) {
			std::swap(pair.first, pair.second);
		}
		a.emplace_back(pair.second);//bigger element in pair
		b.emplace_back(pair);
	}

	PmergeMe::sorter(a);

	std::vector<size_t> order = generateJacobsthalOrder(b.size());//pairless?

	// perform inserts in Jacobsthal order
	for (size_t idx : order) {
		if (idx - 1 < b.size()){
			PmergeMe::binaryInsert(b.at(idx - 1).first, a);
		}
	}
	if (extra) {
		PmergeMe::binaryInsert(*extra, a);
	}

	args = std::move(a);
}

//returns std::deque<int>& ?
template<typename T>
void PmergeMe::sorter(std::deque<T>& args) {

	// std::sort(args.begin(), args.end());
	cout << FMT_YELLOW << "deque sort placeholder.. " << FMT_CLEAR << endl;
	(void)args;
}
