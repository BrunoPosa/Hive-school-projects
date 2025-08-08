#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cerrno>//strerror
#include <stdexcept>
#include <chrono>//date
#include <utility> //move
#include <map>
#include <iomanip>//std::setw

#include <cstring>
#include <limits.h>

# define BTC_RED "\033[31m"
# define BTC_YELLOW "\033[33m"
# define BTC_GREEN "\033[1;32m"
# define BTC_CLEAR "\033[0m"

/*
	-accepts const char* and std::string natively (we want argv[1] to be passed in by pointer, not alloc'd in case of long path)
	Test:
	-ensure all exceptions are accounted for, e.g. for value and date conversions
	-nonexistent lower and upper bound on the first and last values of data.csv
*/
template <typename T> 
class BitcoinExchange {
	static inline constexpr std::string	dataPath_ = "./data.csv";
	static inline constexpr std::string allowedSeparators_ = "|,";
	static inline constexpr std::string allowedDateChars_ = "0123456789-/.";
	std::map<std::chrono::year_month_day, double>	data_;
	std::chrono::year_month_day		parseDate_(const std::string& line);
	double	toPositiveNum(const std::string& numStr);

public:
	BitcoinExchange(){};
	BitcoinExchange(T input);
	BitcoinExchange(const BitcoinExchange& other) = delete;
	BitcoinExchange&	operator=(const BitcoinExchange& other){
		if (this != &other) {
			data_ = std::move(other.data_);
		}
		return *this;
	}
	~BitcoinExchange() {

	}
};

#include "BitcoinExchange.tpp"