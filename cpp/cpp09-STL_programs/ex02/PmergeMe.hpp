#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cctype>//isdigit

# define FMT_RED "\033[31m"
# define FMT_YELLOW "\033[33m"
# define FMT_GREEN "\033[1;32m"
# define FMT_CLEAR "\033[0m"


/*
	"It is strongly advised to implement your algorithm for each container
	and thus to avoid using a generic function." -Is this bc of performance?
*/
template <typename T>
class PmergeMe {
	PmergeMe()						= delete;
	PmergeMe(const PmergeMe& other)	= delete;
	PmergeMe&	operator=(const PmergeMe& other) = delete;
	~PmergeMe()						= delete;

public:
	static bool validateStr(int ac, char **args);
	static void sort(T args);
};

#include "PmergeMe.tpp"