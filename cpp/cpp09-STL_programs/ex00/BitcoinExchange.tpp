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
		throw std::invalid_argument("Could not open infile or datafile: " + string(strerror(errno)));
	}

	//skip first line in datafile
	std::string headline;
	std::getline(datafile_, headline);

	//add data to map [key=date and value=btc rate] - skip empty lines and print errors if any
	run_(datafile_,
		[this](year_month_day ymd, double value) {
        	return this->addToMap_(ymd, value);
    });

	//print value multiplied by exhcange rate for each valid input line and date
	run_(infile_,
		[this](year_month_day ymd, double value) {
        	return this->printCalculation_(ymd, value);
    });

}

/*
	Returns parsed date that is correct
	OR returns empty date on error / incorrect input / nonexisting date
*/
template<typename T>
year_month_day	BitcoinExchange<T>::parseDate_(const std::string& line) {

    std::stringstream	ss(line);
    int y{};
	unsigned int m{}, d{};
	char dash1{}, dash2{};

    if ((ss >> y >> dash1 >> m >> dash2 >> d)
		&& allowedChars_.find(dash1) != string::npos
		&& allowedChars_.find(dash2) != string::npos)
	{
        return std::chrono::year{y}/std::chrono::month{m}/std::chrono::day{d};
    }
    return year_month_day{};
}

template<typename T>
double	BitcoinExchange<T>::toPositiveNum_(const std::string& numStr) {
	try {
		return std::stod(numStr);
	} catch (std::out_of_range) {
		return -1;
	} catch (std::invalid_argument) {
		return -1;
	}
}

template<typename T>
int	BitcoinExchange<T>::printCalculation_(year_month_day date, double amount) {
	if (amount > 0 && amount < 1000) {
		cout << int(date.year()) << "-"
			<< unsigned(date.month()) << "-"
			<< unsigned(date.day())
			<< " => " << amount << " = " 
			<< (data_.lower_bound(date)->first == date
				? (data_.lower_bound(date))->second * amount
				: (--data_.lower_bound(date))->second * amount) << endl;
		return 0;
	} else {
		return -1;
	}
}

template<typename T>
int	BitcoinExchange<T>::addToMap_(year_month_day date, double amount) {
	data_[date] = amount;
	return 0;
}

template<typename T>
void	BitcoinExchange<T>::run_(std::ifstream& file, std::function<int(year_month_day, double)> function) {
	for (string line; std::getline(file, line); ) {
		if (!line.empty()) {
			year_month_day	date	= parseDate_(line);
			std::size_t		sep		= line.find_first_of(allowedSeparators_);
			double			amount 	= toPositiveNum_(line.substr(
				(sep != string::npos ? sep + 1 : 0))
			);

			if (line.find_first_not_of(allowedChars_ + allowedSeparators_) != std::string::npos) {
				cout << BTC_RED << "Error: " << BTC_CLEAR << "forbidden characters! => "  << (line.length() > 42 ? line.substr(0, 39) + "..." : line) << endl;
			} else if (!date.ok()) {
				cout << BTC_RED << "Error: " << BTC_CLEAR << "incorrect date! => " << (line.length() > 42 ? line.substr(0, 39) + "..." : line) << endl;
			} else if (sep == string::npos) {
				cout << BTC_RED << "Error: " << BTC_CLEAR << "could not find separator! => " << (line.length() > 42 ? line.substr(0, 39) + "..." : line) << endl;
			} else if (function(date, amount) == -1) {
				cout << BTC_RED << "Error: " << BTC_CLEAR << "amount out of bounds! => " << (line.length() > 42 ? line.substr(0, 39) + "..." : line) << endl;
			}
		}
	}
}