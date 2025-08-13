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
	size_t pos = 0;

	while ((pos = nextOperationPos_(args_)) != std::string::npos) {
		std::stringstream	expr(args_.substr(0, pos));
		double	operand = 0;

		while (expr >> operand || !expr.eof()) {
			if (expr.fail()) {
				throw std::runtime_error("parse error! possibly invalid or too large number!");
			}
			overflowCheck_(operand);
			stack_.push(operand);
		}

		double	result = 0;
		if (stack_.size() >= 2) {
			result = stack_.top();
			stack_.pop();
			char operation = args_.at(pos);
			if (operation == '+') {
				overflowCheck_(result += stack_.top());
			} else if (operation == '-') {
				overflowCheck_(result = stack_.top() - result);
			} else if (operation == '*') {
				overflowCheck_(result *= stack_.top());
			} else if (operation == '/') {
				if (result == 0) throw std::runtime_error("cannot divide by zero!");
				overflowCheck_(result = stack_.top() / result);
			}
			stack_.pop();
		}
		// cout << result << endl;//step result
		
		stack_.push(result);//I push 0 here in case of stack size < 2
		args_.erase(0, pos + 1);
	}
	// cout << "stack size: " << stack_.size() << endl;
	if (stack_.size() == 1 && args_.find_first_not_of(" \t\v") == std::string::npos) {
		cout << RPN_GREEN << stack_.top() << RPN_CLEAR << endl;
	} else {
		throw std::runtime_error("Error! Invalid expression");
	}
}

//returns pos of next operationChar, ignoring negative numbers ('-' with digit right after, e.g. '-3')
size_t	RPN::nextOperationPos_(const std::string& args) {
	size_t	pos = 0;

	while ((pos = args.find_first_of(operationChars_, pos)) != std::string::npos && args[pos] == '-') {
		if (pos + 1 < args.length() && std::isdigit(args.at(pos + 1))) {
			++pos;//case of negative number, so we continue the search
		} else {
			break;
		}
	}

	return pos;
}

//floating nums don't wrap around on overflow
void	RPN::overflowCheck_(double num) {
	if (std::isfinite(num) == false) throw std::overflow_error("calculation overflowed!");
}
