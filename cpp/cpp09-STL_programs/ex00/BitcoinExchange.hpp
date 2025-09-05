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

template <typename T> 
class BitcoinExchange {
	std::map<std::chrono::year_month_day, double>		data_;
	static inline const std::string	dataPath_			= "./data.csv";
	static inline const std::string	allowedSeparators_	= "|,";
	static inline const std::string	allowedChars_		= "0123456789-/.\t\v ";
	static inline const std::string	allowedData1stLine_	= "date,exchange_rate";
	static inline const std::string	allowedFile1stLine_	= "date | value";
	
	void						run_(std::ifstream& file, std::function<int(std::chrono::year_month_day, double)> function);
	int							addToMap_(std::chrono::year_month_day date, double amount);
	int							printCalculation_(std::chrono::year_month_day date, double amount);
	std::chrono::year_month_day	parseDate_(const std::string& line);
	void						checkHeadline_(std::ifstream& file, const std::string& expectedHeadline);
	double						selectValueFromData_(std::chrono::year_month_day date);
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