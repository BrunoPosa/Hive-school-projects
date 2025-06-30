#pragma once

#include <iostream>
#include <iterator>// std::begin(), std::end(), std::distance
#include <algorithm>
#include <stdexcept>

/*
	returns the index of the first occurrence of num in the container.
	throws std::runtime_error("Value not found") if num is not found
	works with array, vector, list, forward-list, and dequeue
*/
template<typename T>
size_t	easyfind(T& container, int num) {

	auto begin = std::begin(container);
	auto end = std::end(container);

	auto it = std::find(begin, end, num);

	if (it == end) {
		throw std::runtime_error("Value not found");
	}

	return std::distance(begin, it);
}
