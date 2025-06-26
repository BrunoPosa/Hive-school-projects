#pragma once

#include <iostream>
#include <string>
#include <cctype>//std::toupper
#include <cstdlib>//std::srand
#include <ctime>

template <typename T>
void printer(const T& obj) {
	std::cout << obj << std::endl;
}

template <typename T, typename F>
void iter(T* arr, size_t len, F f) {
	if (!arr || !f) {
		return;
	}

	size_t	i = 0;

	while (i != len) {
		f(arr[i]);
		i++;
	}
}
