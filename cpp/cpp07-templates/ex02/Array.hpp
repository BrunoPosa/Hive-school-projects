#pragma once

#include <iostream>
#include <new>
#include <stdexcept>

template <typename T>
class Array {
	T*	arr_;
	unsigned int	n_;

public:
	Array() noexcept : arr_{nullptr}, n_{0} { std::cout << "def. ctor" << std::endl; }
	explicit Array(unsigned int n) : arr_{nullptr}, n_{n} {
		if (n > 0) {
			arr_ = new (std::nothrow) T[n];//Valgrind does not like 'new' exceptions (Hania says so)
			if (!arr_) {
				throw std::runtime_error("new failed to allocate!");
			}
		}
		std::cout << "param. ctor" << std::endl;
	}
	Array(const Array<T>& other) : arr_{nullptr} {
		this->operator=(other);
		std::cout << "copy ctor" << std::endl;
	}
	Array<T>&	operator=(const Array<T>& other) {
		if (this != &other) {
			if (arr_) {
				delete[] arr_;
			}
			if (other.n_ != 0) {
				arr_ = new (std::nothrow) T[other.n_];
				if (!arr_) {
					throw std::runtime_error("new failed to allocate!");
				}
			}
			n_ = other.n_;
			for (unsigned int i = 0; i < n_; i++) {
				arr_[i] = other.arr_[i];
			}
		}
		std::cout << "copy ass" << std::endl;
		return *this;
	}
	~Array() {
		if (arr_) {
			delete[] arr_;
		}
		std::cout << "dtor" << std::endl;
	}

	T&	operator[](const unsigned int index) {
		if (index >= n_ || arr_ == nullptr) {
			throw std::exception();
		}
		return arr_[index];
	}
	const T&	operator[](const unsigned int index) const {
		if (index >= n_ || arr_ == nullptr) {
			throw std::exception();
		}
		return arr_[index];
	}

	unsigned int	size() const noexcept { return n_; }
};
