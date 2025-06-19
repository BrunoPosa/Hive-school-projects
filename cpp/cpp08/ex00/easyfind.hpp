#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <stdexcept>

//should work with array, vector, list, forward-list, dequeue, map, unordered_map, set
//does not work with anything that does not have begin() and end() defined, nor null- or raw pointers
template<typename T>
size_t easyfind(T& container, int num) {
	for (auto it = std::begin(container); it != std::end(container); ++it) {
		if (*it == num) {
			return std::distance(std::begin(container), it);
		}
	}
	throw std::runtime_error("Value not found");
}
