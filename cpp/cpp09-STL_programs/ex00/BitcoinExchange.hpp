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
#include <functional>

#include <cstring>
#include <limits.h>

# define BTC_RED "\033[31m"
# define BTC_YELLOW "\033[33m"
# define BTC_GREEN "\033[1;32m"
# define BTC_CLEAR "\033[0m"

/*
	-accepts const char* and std::string natively (we want argv[1] to be passed in by pointer, not alloc'd in case of long path)
	Test:
	-nonexistent lower and upper bound on the first and last values of data.csv
*/
template <typename T> 
class BitcoinExchange {
	std::map<std::chrono::year_month_day, double>		data_;
	static inline const std::string	dataPath_			= "./data.csv";
	static inline const std::string	allowedSeparators_	= "|,";
	static inline const std::string	allowedChars_		= "0123456789-/.\t\v ";
	void						run_(std::ifstream& file, std::function<int(std::chrono::year_month_day, double)> function);
	int							addToMap_(std::chrono::year_month_day date, double amount);
	int							printCalculation_(std::chrono::year_month_day date, double amount);
	std::chrono::year_month_day	parseDate_(const std::string& line);
	double						selectValueFrom_(std::chrono::year_month_day date);
	double						toPositiveNum_(const std::string& numStr);
	void						errPrint_(std::string msg, std::string& line);
	
public:
	BitcoinExchange(){};
	BitcoinExchange(T input);
	BitcoinExchange(const BitcoinExchange& other) = delete;
	BitcoinExchange&	operator=(const BitcoinExchange& other) = delete;
	~BitcoinExchange(){}
};

#include "BitcoinExchange.tpp"
/*
	Errors:
	-file errors badbit/could not open
	-sys err (bad allocs..)
	-value negative in data.csv or input
	-date incorrect
	-bad syntax/no separator
*/