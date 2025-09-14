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

# define FMT_RED "\033[31m"
# define FMT_YELLOW "\033[33m"
# define FMT_GREEN "\033[1;32m"
# define FMT_CLEAR "\033[0m"

// #define COMPARISON_COUNT //remove 

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

	template<typename T>	static void	runComparison(std::vector<T>& vec, std::deque<T>& dq);
	// static size_t	jacobsthal(size_t n);
	static std::vector<size_t>	generateJacobsthalOrder(size_t size);

	template<typename C>	static double	measureSorting(C& c);
	
	template<typename T>	static void sorter(std::vector<T*>& main);

	template<typename T>	static void sorter(std::deque<T>& args);

	template<typename T>	static bool	isLLessThanR(T& l, T& r);

	template<typename C>	static void	printValues(const C& c, const std::string& sep = " ");

	template<typename T>	static void binaryInsert(T* obj, std::size_t right, std::vector<T*>& vec);
};

#include "PmergeMe.tpp"