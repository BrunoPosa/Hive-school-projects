#include "RPN.hpp"

using std::cout;
using std::endl;
using std::string;

RPN::RPN(){}

RPN::RPN(const RPN& other) : stack_(other.stack_), args_(other.args_) {}

RPN&	RPN::operator=(const RPN& other) {
	if (this != &other) {
		stack_ = other.stack_;
		args_ = other.args_;
	}
	return *this;
}

RPN::RPN(const char * args) : args_(args) {
	if (args_.find_first_not_of(allowedChars_ + operationChars_) != std::string::npos) {
		std::cout << "Error! Allowed chars are: " << allowedChars_ << operationChars_ << std::endl;
	}

	calculate_();
}

/*
	-calculates and prints result of RPN expression
	-expects args string to end with operation char and nothing else
*/
void	RPN::calculate_() {
	// char	operation{};
	int	operand = 0;
	size_t	prevOperationPos = 0;

	while (size_t pos = args_.find_first_of(operationChars_) != std::string::npos) {
		std::stringstream	expression(args_.substr(prevOperationPos, pos));

		if (expression >> operand)
		prevOperationPos = pos;
	}

	if (stack_.size() != 1 || args_.substr(prevOperationPos, args_.size()).empty()) {
		cout << "Error! Invalid expression" << endl;
	}

	cout << stack_.top() << endl;
}