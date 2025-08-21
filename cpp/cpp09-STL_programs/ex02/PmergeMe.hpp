#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cctype>//isdigit
#include <chrono>
#include <algorithm>//std::sort placeholder

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
	static void	measuredSort(std::vector<int>& vec, std::deque<int>& dq);
	static void sort(std::vector<int>& args);
	static void sort(std::deque<int>& args);

	template<typename C>
	static void	printValues(const C& c, const std::string& sep = " ") {
		for (auto it = c.begin(); it != c.end(); ++it) {
			if (it != c.begin()) std::cout << sep;
			std::cout << *it;
		}
		std::cout << std::endl;
	}
};
