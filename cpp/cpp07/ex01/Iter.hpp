#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

template <typename T> void printer(T obj) {
	std::cout << obj << std::endl;
}

template <typename T> void iter(T* arr, size_t len, void (*f)(T)) {
	if (!arr || !f) {
		return;
	}

	size_t	i = 0;

	while (i != len) {
		if (arr + i) {
			f(arr[i]);
		}
		i++;
	}
}
