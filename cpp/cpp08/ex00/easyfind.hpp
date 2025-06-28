#pragma once

#include <iostream>
#include <iterator>// std::begin(), std::end(), std::distance
#include <stdexcept>

//for main()
#include <string>
#include <algorithm>//std::shuffle, std::copy
#include <random>
#include <functional>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>

/*
	returns the index of the first occurrence of num in the container.
	throws std::runtime_error("Value not found") if num is not found
	works with array, vector, list, forward-list, and dequeue
*/
template<typename T>
size_t easyfind(T& container, int num) {
	for (auto it = std::begin(container); it != std::end(container); ++it) {
		if (*it == num) {
			return std::distance(std::begin(container), it);
		}
	}
	throw std::runtime_error("Value not found");
}
