#pragma once

#include <string>
#include <iostream>
#include <cerrno>//strerror
#include <stdexcept>

#include <cstring>
#include <limits.h>

# define BTC_RED "\033[31m"
# define BTC_YELLOW "\033[33m"
# define BTC_GREEN "\033[1;32m"
# define BTC_CLEAR "\033[0m"

/*
	-accepts const char* and std::string natively (we want argv[1] to be passed in by pointer, not alloc'd in case of long path)
*/
template <typename T> 
class BitcoinExchange {
	static inline const std::string datafile_{
		"./data.csv"
	};
	std::ifstream inputFile;
	// bool	validate_();

public:
	BitcoinExchange() = delete;
	BitcoinExchange(T infile);
	// BitcoinExchange(const BitcoinExchange& other) = delete;
	// BitcoinExchange&	operator=(const BitcoinExchange& other);
	~BitcoinExchange() {

	};
};

#include "BitcoinExchange.tpp"