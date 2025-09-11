#include "PmergeMe.hpp"

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

template<typename C>
double	PmergeMe::measureSorting(C& c) {
	auto start = std::chrono::high_resolution_clock::now();
    PmergeMe::sorter(c);
    auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration<double, std::micro>(end - start).count();
}

template<typename T>
void PmergeMe::binaryInsert(T& obj, std::vector<T>& vec) {
	std::size_t	left = 0;
	std::size_t	right = vec.size();

	while (left < right) {
		std::size_t	mid = left + (right - left) / 2;
		if (isLLessThanR(obj, vec[mid])) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	vec.insert(vec.begin() + left, obj);
}