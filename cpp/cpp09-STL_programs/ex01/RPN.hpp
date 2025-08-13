#pragma once

#include <stack>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cctype>//isspace
#include <cmath>//isfinite

# define RPN_RED "\033[31m"
# define RPN_YELLOW "\033[33m"
# define RPN_GREEN "\033[1;32m"
# define RPN_CLEAR "\033[0m"

class RPN {
	std::stack<double>		stack_;
	std::string			args_;
	const std::string	allowedChars_ = "0123456789 \t\v";
	const std::string	operationChars_	= "+-/*";
	size_t	nextOperationPos_(const std::string& args);
	void	calculate_();
	void	overflowCheck_(double num);
public:
	RPN();
	RPN(const RPN& other);
	RPN&	operator=(const RPN& other);
	~RPN() = default;
	RPN(const char * args);
};