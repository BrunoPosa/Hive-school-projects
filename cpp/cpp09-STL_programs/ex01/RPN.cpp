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
	double	operandCount = 0;

	while ((pos = nextOperationPos_(args_)) != std::string::npos) {
		std::stringstream	expr(args_.substr(0, pos));
		double	operand = 0;

		while (expr >> operand || !expr.eof()) {
			if (expr.fail()) {
				throw std::runtime_error("parse error! possibly invalid or too large number!");
			}
			overflowCheck_(operand);
			stack_.push(operand);
			operandCount++;
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

		args_.erase(0, pos + 1);
		stack_.push(result);
	}

	if (stack_.size() == 1 && operandCount >= 2 && args_.find_first_not_of(" \t\v") == std::string::npos) {
		cout << stack_.top() << endl;
	} else {
		throw std::runtime_error("Error! Invalid expression");
	}
}

//returns pos of next operationChar, ignoring negative numbers ('-' with a digit right after it)
size_t	RPN::nextOperationPos_(const std::string& args) {
	size_t	pos = 0;

	while ((pos = args.find_first_of(operationChars_, pos)) != std::string::npos && args[pos] == '-') {
		if (pos + 1 < args.length() && std::isdigit(args.at(pos + 1))) {
			++pos; //case of negative number, so we continue the search
		} else {
			break;
		}
	}

	return pos;
}

void	RPN::overflowCheck_(double num) {
	if (std::isfinite(num) == false) throw std::overflow_error("calculation overflowed!");
}
