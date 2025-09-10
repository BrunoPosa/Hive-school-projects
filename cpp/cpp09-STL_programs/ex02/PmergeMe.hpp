#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cctype>//isdigit
#include <chrono>
#include <algorithm>//std::sort placeholder, std::equal
#include <iomanip>
#include <optional>

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
	static bool validateStr(int ac, char **args);
	static void	runComparison(std::vector<int>& vec, std::deque<int>& dq);

	template<typename C>	static double	measureSorting(C& c);
	
	template<typename T>	static void sorter(std::vector<T>& args);

	template<typename T>	static void sorter(std::deque<T>& args);

	template<typename T>	static bool	isLLessThanR(T& l, T& r);

	template<typename C>	static void		printValues(const C& c, const std::string& sep = " ");
};

#include "PmergeMe.tpp"