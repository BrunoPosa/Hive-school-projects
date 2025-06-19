#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>//minmax_element
#include <stdexcept>
#include <set>//std::set
#include <utility>//std::move
#include <limits>

//main()
#include <functional>//std::function
#include <numeric>//std::iota

class Span {
	std::vector<int>	numbers_;

public:
	Span()	= default;
	explicit Span(unsigned int N);
	Span(const Span& other);
	Span&	operator=(const Span& other);
	~Span()	= default;

	size_t	shortestSpan() const;
	size_t	longestSpan() const;
	void	addNumber(int num);
	template<typename It> void	addRange(It begin, It end) {
		while (begin != end) {
			addNumber(*begin);
			begin++;
		}
	}
};
