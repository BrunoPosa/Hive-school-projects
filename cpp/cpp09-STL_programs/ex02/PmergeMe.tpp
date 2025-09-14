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
	size = vec.size();
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


/*
 does not sort in less than max moves for 9 numbers e.g. with the following numbers:
 4 8 5 7 0 9 10 6 3
 -HANDLE DUPLICATES?
 -Should i just have jacobstahl order start with 3? instead of 1
 -why do i keep the already inserted first b value (from smallest a pair) in the b array? it might be messing up the ideal jacobstahl order
 -check if sorted to stop early
*/
//returns std::vector<int>& ?
//sorts vector containing any type of elements
//ideally avoids moving elements until last moment (sorts indices/pointers)
template<typename T>
void PmergeMe::sorter(std::vector<T*>& main) {

	std::size_t n = main.size();
	if (n == 2) {//or 1
		if (!isLLessThanR(*main.at(0), *main.at(1))) {
			std::swap(main.at(0), main.at(1));
		}
		return;
	} else if (n == 1) {cout << "N ======= 1 !!!!!!!!!!" << endl; return; }
	T* extra = nullptr;
	bool pairless = n % 2;
	if (pairless) {
		extra = main.at(n - 1);
		// cout << "extra:" << *extra << endl;
	}
	std::vector<T*>a;
	std::vector<std::pair<T*, T*>>b;
	a.reserve(n / 2);
	b.reserve(n / 2);

	for (std::size_t i = 0; i < n - pairless; i += 2) {
		std::pair<T*, T*> pair(main.at(i), main.at(i + 1));//rm .at, use forward?
		if (!isLLessThanR(*pair.first, *pair.second)) {
			std::swap(pair.first, pair.second);
		}
		a.emplace_back(pair.second);//bigger element in pair
		b.emplace_back(pair);
	}

	cout << "----\n" << ">> IN - level " << size / main.size() << " of recursion" << endl; 
	cout << FMT_YELLOW << "  comparisons so far: " << FMT_CLEAR << comparisons << endl;
	cout << "a: "; for (auto& it : a) {cout << std::setw(2) << *it << " "; } cout << endl;
	cout << "b: "; for (auto& it : b) {cout << std::setw(2) << *it.first << " ";} cout << std::setw(2) << ((extra) ? *extra : -1) << endl;

	PmergeMe::sorter(a);

	cout << "----\n" << "<< OUT - level " << size / main.size() << " of recursion" << endl; 
	cout << "a: "; for (auto& it : a) {cout << std::setw(2) << *it << " "; } cout << endl;
	cout << "b: "; for (auto& it : b) {cout << std::setw(2) << *it.first << " ";} cout << std::setw(2) << ((extra) ? *extra : -1) << endl;

	
	T*	ignore = nullptr;
	//for smallest element in a, which is a[0], we insert its pair to the left without comparisons
	for (std::size_t i = 0; i < b.size(); i++) {
		if (b.at(i).second == a.at(0)) {
			ignore = b.at(i).second;
			a.insert(a.begin(), b.at(i).first);
			cout << FMT_YELLOW << "instantly inserted " << *b.at(i).first << ", " << b.at(i).first << FMT_CLEAR<< endl;
			b.erase(b.begin() + i);
			break;
		}
	}
	// perform ordered inserts
	std::vector<size_t> order = generateJacobsthalOrder(b.size() + pairless);
	for (size_t idx : order) {
		if (idx - 1 == b.size() && extra) {
			PmergeMe::binaryInsert(extra, a.size(), a);
			cout << FMT_YELLOW << "inserted " << *extra << FMT_CLEAR << endl;
			cout <<  FMT_YELLOW << "  comparisons so far: " << FMT_CLEAR << comparisons << endl;
			extra = nullptr;
			continue;
		}
		if (b.at(idx - 1).second == ignore) {cout << "IGNORING : "<< *b.at(idx - 1).first << " == ignored pair in a:" << *ignore << ", " << b.at(idx - 1).second << endl;
			continue;}
		auto it = std::find(a.begin(), a.end(), b.at(idx - 1).second);
		std::size_t	right = 0;//right edge of search field for binary search
		if (it == a.end()) {
			right = a.size();
		} else {
			right = std::distance(a.begin(), it);
		}
		cout << FMT_GREEN << "right=" << FMT_CLEAR << right << endl;
		PmergeMe::binaryInsert(b.at(idx - 1).first, right, a);
		cout << FMT_YELLOW << "inserted " << *b.at(idx - 1).first << ", " << b.at(idx - 1).first << FMT_CLEAR << endl;
		cout <<  FMT_YELLOW << "  comparisons so far: " << FMT_CLEAR << comparisons << endl;
	}
	if (extra) {
		PmergeMe::binaryInsert(extra, a.size(), a);
		cout << FMT_YELLOW << "inserted " << *extra << FMT_CLEAR << endl;
		cout <<  FMT_YELLOW << "  comparisons so far: " << FMT_CLEAR << comparisons << endl;
	}

	if (a.size() != n) {
		std::cerr << "ERROR: after insertion a.size()=" << a.size() << " expected=" << n << ", b size=" << b.size() << '\n';}

	cout << "a: "; for (auto& it : a) {cout << *it << " "; } cout << endl;

	main = std::move(a);
}

//returns std::deque<int>& ?
template<typename T>
void PmergeMe::sorter(std::deque<T>& main) {

	// std::sort(main.begin(), main.end());
	// cout << FMT_YELLOW << "deque sort placeholder.. " << FMT_CLEAR << endl;
	(void)main;
}

template<typename T>
void PmergeMe::binaryInsert(T* obj, std::size_t right, std::vector<T*>& vec) {
	assert(right <= vec.size());
	
	std::size_t	left = 0;
// cout << "inserting: " << *obj << ", sizeof vec in BinaryInsert: " << vec.size() << " and right is " << right << endl;
	while (left < right) {
		std::size_t	mid = left + (right - left) / 2;
		cout << FMT_RED << "insertion - comparing " << *obj << " to " << *vec.at(mid) << FMT_CLEAR << endl;
		if (isLLessThanR(*obj, *vec.at(mid))) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	vec.insert(vec.begin() + left, obj);
}
