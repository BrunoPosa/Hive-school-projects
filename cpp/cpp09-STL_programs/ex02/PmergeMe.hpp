#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cctype>//isdigit
#include <chrono>
#include <algorithm>//std::sort placeholder, std::equal
#include <iomanip>

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
	static bool validateStr(int ac, char **args);
	static void	runComparison(std::vector<int>& vec, std::deque<int>& dq);

	template<typename C>
	static double	measureSorting(C& c);
	
	template<typename T>
	static void sort(std::vector<T>& args);

	template<typename T>
	static void sort(std::deque<T>& args);

	template<typename C>
	static void		printValues(const C& c, const std::string& sep = " ");
};

#include "PmergeMe.tpp"