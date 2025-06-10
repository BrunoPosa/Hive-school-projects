#ifndef STARTWITHAFEWFUNCTIONS_HPP
# define STARTWITHAFEWFUNCTIONS_HPP

#include <iostream>
#include <string>

template <typename T> T min(const T& l, const T& r) {
	return l < r	? l : r;
}

template <typename T> T max(const T& l, const T& r) {
	return l > r	? l : r;
}

template <typename T> void swap(T& l, T& r) {
	T temp = l;
	l = r;
	r = temp;
}

#endif