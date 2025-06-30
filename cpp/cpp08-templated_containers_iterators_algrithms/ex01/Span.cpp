#include "Span.hpp"

Span::Span(){};

Span::Span(unsigned int N) {
	numbers_.reserve(N);
}

Span::Span(const Span& other) : numbers_{other.numbers_} {}

Span&	Span::operator=(const Span& other) {
	if (this != &other) {
		numbers_ = other.numbers_;
	}
	return *this;
}

Span::~Span(){};

void	Span::addNumber(int num) {
	if (numbers_.size() == numbers_.capacity()) {
		throw std::overflow_error("Max N reached!");
	}
	numbers_.push_back(num);
}

size_t	Span::shortestSpan() const {
	if (numbers_.size() < 2) {
		throw std::runtime_error("No span can be found! You need at least 2 numbers in vector.");
	}

	std::set<int> sortedDeduplicated(numbers_.begin(), numbers_.end());
	if (sortedDeduplicated.size() < numbers_.size()) {
		return 0;//means there were duplicates so shortest span is 0
	} else {
		size_t minSpan = std::numeric_limits<size_t>::max();
		size_t span = 0;
		for (auto it = sortedDeduplicated.begin(); std::next(it) != sortedDeduplicated.end(); ++it) {
			if ((span = static_cast<ssize_t>(*std::next(it)) - static_cast<ssize_t>(*it)) < minSpan) {
				minSpan = span;
			}
		}
		return minSpan;
	}
}

size_t	Span::longestSpan() const {
	if (numbers_.size() < 2) {
		throw std::runtime_error("No span can be found! You need at least 2 numbers in vector.");
	}
	auto [minIt, maxIt] = std::minmax_element(numbers_.begin(), numbers_.end());
	return (static_cast<ssize_t>(*maxIt) - static_cast<ssize_t>(*minIt));//important to cast
}
