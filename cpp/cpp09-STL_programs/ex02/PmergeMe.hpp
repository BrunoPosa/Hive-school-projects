#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cctype>//isdigit
#include <chrono>
#include <algorithm>//std::sort placeholder, std::equal, std::upper_bound
#include <iomanip>
#include <optional>
#include <cassert>
#include <iomanip> //setw
#include <type_traits>//?
#include <iterator>

# define FMT_RED "\033[31m"
# define FMT_YELLOW "\033[33m"
# define FMT_GREEN "\033[1;32m"
# define FMT_CLEAR "\033[0m"

//const?
class PmergeMe {
	PmergeMe()						= delete;
	PmergeMe(const PmergeMe& other)	= delete;
	PmergeMe&	operator=(const PmergeMe& other) = delete;
	~PmergeMe()						= delete;

public:
	static size_t	comparisons;
	static size_t	size;
	static bool validateStr(int ac, char **args);
	static std::vector<size_t>	generateJacobsthalOrder(size_t size);
	
	template<typename Ptr>	static void adjustB(std::vector<Ptr>& a, std::vector<std::pair<Ptr, Ptr>>& b);

	template<typename T>	static void	runComparison(std::vector<T>& vec, std::deque<T>& dq);

	template<typename C>	static double	measureSorting(C& c);
	
	template<typename C>	static void sorter(C& main);

	template<typename T>	static bool	isLLessThanR(T& l, T& r);

	template<typename C>	static void	printValues(const C& c, const std::string& sep = " ");

	template<typename C>	static void binaryInsert(typename C::value_type obj, std::size_t right, C& vec);

	template<typename C>	static bool	isSorted(C& c);
};

#include "PmergeMe.tpp"