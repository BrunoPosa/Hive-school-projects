#include "PmergeMe.hpp"

using std::cout;
using std::endl;

template<typename T>
void	PmergeMe::runComparison(std::vector<T>& vec, std::deque<T>& dq) {
	PmergeMe::size = vec.size();

	//make mirror vec and dq containers with pointers to original container members, to be used in actual sorting
	std::vector<T*> vecRefs;
	vecRefs.reserve(PmergeMe::size);
	for (auto &v : vec) vecRefs.push_back(&v);
	std::deque<T*>	dqRefs;
	for (auto &v : dq) dqRefs.push_back(&v);

	#ifdef TRACE
		cout << "--------------1st container--------------" << endl;
	#endif
	PmergeMe::comparisons = 0;
	auto durVec = PmergeMe::measureSorting(vecRefs);
	size_t compsVec = PmergeMe::comparisons;

	#ifdef TRACE
		cout << "--------------2nd container--------------" << endl;
	#endif
	PmergeMe::comparisons = 0;
	auto durDq = PmergeMe::measureSorting(dqRefs);
	size_t compsDq = PmergeMe::comparisons;

	if (isSorted(vecRefs) && isSorted(dqRefs) && std::equal(vec.begin(), vec.end(), dq.begin(), dq.end()) && compsVec == compsDq) {
		PmergeMe::printValues(dqRefs);
	} else {
		cout << FMT_RED << " sorting failed!" << FMT_CLEAR << endl;
	}

	cout << "\nTime to process a range of " << vec.size() << " elements with std::vector : "
    	<< std::fixed << std::setprecision(3) << durVec << " µs" << endl;

	cout << "Time to process a range of " << dq.size() << " elements with std::deque  : "
    	<< std::fixed << std::setprecision(3) << durDq << " µs" << endl;

	#ifdef COMPARISON_COUNT
		cout << "comparisons: " << compsVec << endl;
	#endif
}

template<typename C>
double	PmergeMe::measureSorting(C& c) {
	if (isSorted(c)) return 0;

	auto start = std::chrono::high_resolution_clock::now();
    PmergeMe::sorter(c);
    auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration<double, std::micro>(end - start).count();
}

template<typename C>
void PmergeMe::sorter(C& main) {
    using Ptr = typename C::value_type;
    static_assert(std::is_pointer_v<Ptr>, "Container must hold pointers (T*)");

	std::size_t n = main.size();
	if (n <= 1) return;
	if (n == 2) {
		if (!isLLessThanR(*main[0], *main[1]))	std::swap(main[0], main[1]);
		return;
	}

	Ptr extra = nullptr;
	bool pairless = n % 2;
	if (pairless) extra = main[n - 1];

	std::vector<Ptr>	a;
	std::vector<std::pair<Ptr, Ptr>>	b;
	a.reserve(n / 2);
	b.reserve(n / 2);

	//split into pairs, bigger element pointers go to A and the smaller element pointers stay in B while still paired to their respective As
	for (std::size_t i = 0; i < n - pairless; i += 2) {
		std::pair<Ptr, Ptr> pair(main[i], main[i + 1]);
		if (!isLLessThanR(*pair.first, *pair.second)) std::swap(pair.first, pair.second);
		a.emplace_back(pair.second);
		b.emplace_back(pair);
	}

	#ifdef TRACE
		cout << "----\n" << ">> IN - level " << size / main.size() << " of recursion" << endl; 
		cout << FMT_YELLOW << "  comparisons so far: " << FMT_CLEAR << comparisons << endl;
		cout << "a: "; for (auto& it : a) {cout << std::setw(2) << *it << " "; } cout << endl;
		cout << "b: "; for (auto& it : b) {cout << std::setw(2) << *it.first << " ";} cout << std::setw(2) << ((extra) ? *extra : -1) << endl;
	#endif

	PmergeMe::sorter(a);//A is sorted after this
	adjustB(a, b);//reorder B so that its member pairs align with newly sorted A indexes

	#ifdef TRACE
		cout << "----\n" << "<< OUT - level " << size / main.size() << " of recursion" << endl; 
		cout << "a: "; for (auto& it : a) {cout << std::setw(2) << *it << " "; } cout << endl;
		cout << "b: "; for (auto& it : b) {cout << std::setw(2) << *it.first << " ";} cout << std::setw(2) << ((extra) ? *extra : -1) << endl;
	#endif

	// perform ordered insertions
	std::vector<size_t> order = generateJacobsthalOrder(b.size() + pairless);
	for (size_t idx : order) {
		if (idx > b.size() && extra != nullptr) {
			PmergeMe::binaryInsert<std::vector<Ptr>>(extra, a.size(), a);
			extra = nullptr;
			continue;
		}

		//find right edge of search field for binary search by looking for the index of B's pair in A
		auto it = std::find(a.begin(), a.end(), b[idx - 1].second);
		std::size_t	right = std::distance(a.begin(), it);
		PmergeMe::binaryInsert<std::vector<Ptr>>(b[idx - 1].first, right, a);
	}

	#ifdef TRACE
		cout << "a: "; for (auto& it : a) {cout << *it << " "; } cout << endl;
	#endif
	main.assign(a.begin(), a.end());
}

template<typename C>
void PmergeMe::binaryInsert(typename C::value_type obj, std::size_t right, C& vec) {
    using Ptr = typename C::value_type;
    static_assert(std::is_pointer_v<Ptr>, "Container must hold pointers (T*)");

    std::size_t left = 0;
    while (left < right) {
        std::size_t mid = left + (right - left) / 2;
        if (isLLessThanR(*obj, *vec[mid])) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
	#ifdef TRACE
		cout << FMT_GREEN << "right edge=" << FMT_CLEAR << right << endl;
		cout << FMT_YELLOW << "inserted " << *obj << FMT_CLEAR << endl;
		cout <<  FMT_YELLOW << "  comparisons so far: " << FMT_CLEAR << PmergeMe::comparisons << endl;
	#endif
    vec.insert(vec.begin() + left, obj);
}

template<typename Ptr>
void PmergeMe::adjustB(std::vector<Ptr>& a, std::vector<std::pair<Ptr, Ptr>>& b) {
    std::vector<std::pair<Ptr, Ptr>> temp;
    temp.reserve(b.size());

    for (std::size_t i = 0; i < a.size(); ++i) {
        for (std::size_t j = 0; j < b.size(); ++j) {
            if (a[i] == b[j].second) {
                // insert in the same relative position as 'a'
                temp.insert(temp.begin() + i, b[j]);
                break;
            }
        }
    }
    b = std::move(temp);
}

template<typename C>
bool	PmergeMe::isSorted(const C& c) {
	if (c.empty() || c.size() == 1) return true;

    for (auto it = c.begin(); std::next(it) != c.end(); ++it) {
        auto nxt = std::next(it);
        if (**it > **nxt) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool	PmergeMe::isLLessThanR(const T& l, const T& r) {
	PmergeMe::comparisons++; return l < r;
}

template<typename C>
void	PmergeMe::printValues(const C& c, const std::string& sep) {
	for (auto it = c.begin(); it != c.end(); ++it) {
		if (it != c.begin()) std::cout << sep;
		std::cout << **it;
	}
	std::cout << std::endl;
}
