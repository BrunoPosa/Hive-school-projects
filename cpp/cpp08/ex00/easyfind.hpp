#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

//container might be array, vector, list, forward-list, and dequeue
// template<typename T>
// bool easyfind(T& container, int num) {
// 	for (auto it : container) {
// 		if (it == num) {
// 			return true;
// 		}
// 	}
// 	return false;
// }
template<typename T>
size_t easyfind(T& container, int num) {
	for (auto it = container.begin(); it != container.end(); ++it) {
		if (*it == num) {
			return std::distance(container.begin(), it);
		}
	}
	throw std::runtime_error("Value not found");
}