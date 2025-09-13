#include "PmergeMe.hpp"

using std::cout;
using std::endl;

template<typename T>
bool	PmergeMe::isLLessThanR(T& l, T& r) { comparisons++; return l < r; }

template<typename C>
void	PmergeMe::printValues(const C& c, const std::string& sep) {
	for (auto it = c.begin(); it != c.end(); ++it) {
		if (it != c.begin()) std::cout << sep;
		std::cout << *it;
	}
	std::cout << std::endl;
}

template<typename T>
void	PmergeMe::runComparison(std::vector<T>& vec, std::deque<T>& dq) {
	std::vector<T*> vecRefs;
	vecRefs.reserve(vec.size());
	for (auto &v : vec) {
    	vecRefs.push_back(&v);
	}
	auto durVec = PmergeMe::measureSorting(vecRefs);
	auto durDq = PmergeMe::measureSorting(dq);

	for (auto& num : vecRefs) {
		cout << *num << " ";
	}

	// if (std::equal(vec.begin(), vec.end(), dq.begin(), dq.end())) {
	// 	PmergeMe::printValues(vec);
	// } else {
	// 	cout << " sorting failed!";
	// }

	cout << "\nTime to process a range of " << vec.size()
		<< " elements with std::vector<int> : "
    	<< std::fixed << std::setprecision(3) << durVec << " µs" << endl;

	cout << "Time to process a range of " << dq.size()
		<< " elements with std::deque<int>  : "
    	<< std::fixed << std::setprecision(3) << durDq << " µs" << endl;

	#ifdef COMPARISON_COUNT
		cout << "comparisons: " << PmergeMe::comparisons << endl;
	#endif
}

template<typename C>
double	PmergeMe::measureSorting(C& c) {
	auto start = std::chrono::high_resolution_clock::now();
    PmergeMe::sorter(c);
    auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration<double, std::micro>(end - start).count();
}

//returns std::vector<int>& ?
//sorts vector containing any type of elements
//ideally avoids moving elements until last moment (sorts indices/pointers)
template<typename T>
void PmergeMe::sorter(std::vector<T*>& args) {

	std::size_t n = args.size();
	if (n <= 2) {//or 1
		if (!isLLessThanR(*args.at(0), *args.at(1))) {
			std::swap(args.at(0), args.at(1));
		}
		return;
	}
	T* extra = nullptr;
	bool pairless = n % 2;
	if (pairless) {
		extra = args.at(n - 1);
		// cout << "extra:" << *extra << endl;
	}
	std::vector<T*>a;
	std::vector<std::pair<T*, T*>>b;
	a.reserve(n / 2);
	b.reserve(n / 2);

	for (std::size_t i = 0; i < n - pairless; i += 2) {
		std::pair<T*, T*> pair(args.at(i), args.at(i + 1));//rm .at, use forward?
		if (!isLLessThanR(*pair.first, *pair.second)) {
			std::swap(pair.first, pair.second);
		}
		a.emplace_back(pair.second);//bigger element in pair
		b.emplace_back(pair);
	}
	// cout << "b: ";
	// for (auto& it : b) {cout << *it.first << " "; }
	// cout << endl;

	PmergeMe::sorter(a);

	std::vector<size_t> order = generateJacobsthalOrder(b.size());//pairless?

	// perform ordered inserts
	for (size_t idx : order) {
		//for smallest element in a, we insert its pair to the left without comparisons
		if (idx == 1) {
			for (std::size_t i = 0; i < b.size(); i++) {
				if (b.at(i).second == a.at(0)) {
					a.insert(a.begin(), b.at(i).first);
					// cout << "1st inserted " << *b.at(i).first << endl;
					break;
				}
			}
		} else {
			auto it = std::find(a.begin(), a.end(), b.at(idx - 1).second);
			std::size_t	right = 0;
			if (it == a.end()) {
				right = a.size();
			} else {
				right = std::distance(a.begin(), it);
			}
			PmergeMe::binaryInsert(b.at(idx - 1).first, right, a);
		}
	}
	if (extra) {
		PmergeMe::binaryInsert(extra, a.size(), a);
	}
	if (a.size() != n) {
		std::cerr << "ERROR: after insertion a.size()=" << a.size() << " expected=" << n << "b size=" << b.size() << '\n';}
	// cout << "a: ";
	// for (auto& it : a) {cout << *it << " "; }
	// cout << endl;
	args = std::move(a);
}

//returns std::deque<int>& ?
template<typename T>
void PmergeMe::sorter(std::deque<T>& args) {

	// std::sort(args.begin(), args.end());
	// cout << FMT_YELLOW << "deque sort placeholder.. " << FMT_CLEAR << endl;
	(void)args;
}

template<typename T>
void PmergeMe::binaryInsert(T* obj, std::size_t right, std::vector<T*>& vec) {
	std::size_t	left = 0;
// cout << "inserting: " << *obj << ", sizeof vec in BinaryInsert: " << vec.size() << " and right is " << right << endl;
	while (left < right) {
		std::size_t	mid = left + (right - left) / 2;
		if (isLLessThanR(*obj, *vec[mid])) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	vec.insert(vec.begin() + left, obj);
}