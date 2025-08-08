#include "BitcoinExchange.hpp"

using std::chrono::year_month_day;
using std::string;
using std::cout;
using std::endl;

template<typename T>
BitcoinExchange<T>::BitcoinExchange(T input) {

	std::ifstream infile_{input};
	std::ifstream datafile_{dataPath_};

	if (!datafile_.is_open() || !infile_.is_open()) {
		throw std::invalid_argument("Could not open insfile or datafile: " + string(strerror(errno)));
	}

	//1. parse datafile
	for (string line; std::getline(datafile_, line); ) {
		if (!line.empty()) {
			year_month_day	date	= parseDate_(line);
			std::size_t		sep		= line.find_first_of(allowedSeparators_);
			double			rate 	= toPositiveNum(line.substr(
				(sep != string::npos ? sep + 1 : 0))
			);

			if (date.ok() && sep != string::npos) {
				data_[date] = rate;
			}
		}
	}

	//2. validate, parse, and calculate infile line in loop
	for (string line; std::getline(infile_, line); ) {
		if (!line.empty()) {
			year_month_day	date	= parseDate_(line);
			std::size_t		sep		= line.find_first_of(allowedSeparators_);
			double			amount 	= toPositiveNum(line.substr(
				(sep != string::npos ? sep + 1 : 0))
			);

			if (date.ok() && sep != string::npos && amount > 0 && amount < 1000) {
				cout << int(date.year()) << "-"
					<< unsigned(date.month()) << "-"
					<< unsigned(date.day())
					<< " => " << amount << " = " 
					<< (data_.lower_bound(date)->first == date
						? (data_.lower_bound(date))->second * amount
						: (--data_.lower_bound(date))->second * amount) << endl;
			} else {
				cout << "Error: " << " => " << (line.length() > 42 ? line.substr(0, 39) + "..." : line) << endl;
			}
		}
	}

}

// template<typename T>
// bool	BitcoinExchange<T>::isValidDate_(const std::string& line, std::string separator) {

// 	std::istringstream iss(line);
// 	string dateStr;//line.substr(0, line.find_first_not_of(dateCharset))
// 	if (iss) {
// 		iss >> std::skipws >> dateStr;
// 		cout << dateStr << endl;
// 	}

// 	return parseDate_(dateStr).ok();
// }

/*
	Returns parsed date that is correct
	OR returns empty date on error / incorrect input / nonexisting date
*/
template<typename T>
year_month_day	BitcoinExchange<T>::parseDate_(const std::string& line) {

    std::stringstream	ss(line);
    int y{};
	unsigned int m{}, d{};
	char dash1{}, dash2;

    if ((ss >> y >> dash1 >> m >> dash2 >> d)
		&& allowedDateChars_.find(dash1) != string::npos
		&& allowedDateChars_.find(dash2) != string::npos)
	{
		// cout << y << "|" << m << "|" << d << "|" << endl;
        return std::chrono::year{y}/std::chrono::month{m}/std::chrono::day{d};
    }
    return year_month_day{};
}

template<typename T>
double	BitcoinExchange<T>::toPositiveNum(const std::string& numStr) {
	try {
		return std::stod(numStr);
	} catch (std::out_of_range) {
		return -1;
	} catch (std::invalid_argument) {
		return -1;
	}
}