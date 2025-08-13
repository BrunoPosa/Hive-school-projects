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
		throw std::invalid_argument("Error! Allowed chars are numerical digits, spaces and tabs, and " + std::string(operationChars_));
	}

	calculate_();
}

/*
	-calculates and prints result of RPN expression
	-expects args string to end with operation char and nothing else
*/
void	RPN::calculate_() {
	size_t	prevOperationPos = 0;
	size_t pos = 0;

	while ((pos = args_.find_first_of(operationChars_)) != std::string::npos) {
		std::stringstream	expr(args_.substr(prevOperationPos, pos));
		int	operand = 0;

		while (expr >> operand || !expr.eof()) {
			if (expr.fail()) {
				expr.clear();
				string dump;
				expr >> dump;
				continue;
			}
			stack_.push(operand);
		}

		ssize_t	result = 0;
		if (stack_.size() >= 2) {
			result = stack_.top();
			stack_.pop();
			char operation = args_.at(pos);
			if		(operation == '+') result += stack_.top();
			else if (operation == '-') result = stack_.top() - result;
			else if (operation == '*') result *= stack_.top();
			else if (operation == '/') {
				if (result == 0) throw std::runtime_error("cannot divide by zero!");
				result = stack_.top() / result;
			}
			stack_.pop();
		}
		// cout << result << endl;//step result
		stack_.push(result);
		args_.erase(prevOperationPos, pos + 1);
	}
	// cout << "stack size: " << stack_.size() << endl;
	if (stack_.size() == 1 && args_.substr(prevOperationPos, args_.size()).empty()) {
		cout << stack_.top() << endl;
	} else {
		throw std::runtime_error("Error! Invalid expression");
	}
}