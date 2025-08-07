#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cerrno>//strerror
#include <stdexcept>
#include <chrono>//date
#include <utility> //move

#include <cstring>
#include <limits.h>

# define BTC_RED "\033[31m"
# define BTC_YELLOW "\033[33m"
# define BTC_GREEN "\033[1;32m"
# define BTC_CLEAR "\033[0m"


# define BTC_DATAFILE "./data.csv"
/*
	-accepts const char* and std::string natively (we want argv[1] to be passed in by pointer, not alloc'd in case of long path)
	Test:
	-
*/
template <typename T> 
class BitcoinExchange {
	std::ifstream datafile_;//make this a map
	std::ifstream infile_;
	std::chrono::year_month_day	parseDate_(const std::string& date);
	bool	isValidDate_(const std::string& line);

public:
	BitcoinExchange(){};
	BitcoinExchange(T input);
	BitcoinExchange(const BitcoinExchange& other) = delete;
	BitcoinExchange&	operator=(const BitcoinExchange& other){
		if (this != &other) {
			datafile_ = std::move(other.datafile_);
			infile_ = std::move(other.infile_);
		}
		return *this;
	}
	~BitcoinExchange() {

	}
};

#include "BitcoinExchange.tpp"