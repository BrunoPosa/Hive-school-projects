#pragma once

#include <stack>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>


# define RPN_RED "\033[31m"
# define RPN_YELLOW "\033[33m"
# define RPN_GREEN "\033[1;32m"
# define RPN_CLEAR "\033[0m"

class RPN {
	std::stack<int>		stack_;
	std::string			args_;
	const std::string	allowedChars_ = "0123456789 \t\v";
	const std::string	operationChars_	= "+-/*";

public:
	RPN();
	RPN(const RPN& other);
	RPN&	operator=(const RPN& other);
	~RPN() = default;
	explicit RPN(const char * args);

	void	calculate_();
};