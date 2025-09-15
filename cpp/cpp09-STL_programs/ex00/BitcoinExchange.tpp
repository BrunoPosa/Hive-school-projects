#include "BitcoinExchange.hpp"

using std::chrono::year_month_day;
using std::string;
using std::cout;
using std::endl;

template<typename T>
BitcoinExchange<T>::BitcoinExchange(T input) {

	std::ifstream infile_{input};
	std::ifstream datafile_{dataPath_};

	if (datafile_.is_open() == false || infile_.is_open() == false) {
		throw std::invalid_argument("Could not open infile or datafile: " + string(strerror(errno)));
	}

	checkHeadline_(datafile_, allowedData1stLine_);
	checkHeadline_(infile_, allowedFile1stLine_);
	if (datafile_.eof() || infile_.eof()) return;

	//add data to map [key=date ; value=btc rate] - skip empty lines and print errors if any
	run_(datafile_,
		[this](year_month_day ymd, double value) {
        	return this->addToMap_(ymd, value);
    });

	//print value multiplied by exchange rate for each valid input line and date
	run_(infile_,
		[this](year_month_day ymd, double value) {
        	return this->printCalculation_(ymd, value);
    });

}

//run given function on the lines of the file, skipping empty lines and validating everything
template<typename T>
void	BitcoinExchange<T>::run_(std::ifstream& file, std::function<int(year_month_day, double)> function) {
	for (string line; std::getline(file, line); ) {
		if (line.empty() == false) {
			year_month_day	date 		= parseDate_(line);
			std::size_t		separator	= line.find_first_of(allowedSeparators_);
			double			amount		= toPositiveNum_(line.substr(
				(separator != string::npos ? separator + 1 : 0))
			);

			if (line.find_first_not_of(allowedChars_ + allowedSeparators_) != std::string::npos) {
				errPrint_("forbidden characters!", line);
			} else if (date.ok() == false) {
				errPrint_("incorrect date!", line);
			} else if (separator == string::npos) {
				errPrint_("could not find separator!", line);
			} else if (function(date, amount) == -1) {
				errPrint_("amount out of bounds!", line);
			}
		}
	}
}

/*
	Returns parsed date if correct
	OR empty date if incorrect input / nonexisting date
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
		if (y >= (int)std::chrono::year::min() && y <= (int)std::chrono::year::max()) {
        	return std::chrono::year{y}/std::chrono::month{m}/std::chrono::day{d};
		}
    }
    return year_month_day{};
}

template<typename T>
double	BitcoinExchange<T>::toPositiveNum_(const std::string& numStr) {
	try {
		return std::stod(numStr);
	} catch (std::out_of_range&) {
		return -1;
	} catch (std::invalid_argument&) {
		return -1;
	}
}

template<typename T>
double	BitcoinExchange<T>::selectValueFromData_(year_month_day date) {
	double	value = 0;
	auto it = data_.lower_bound(date);

	if (it != data_.end() && it->first == date) {
		value = it->second;
	} else if (it != data_.begin()) {
		--it;
		value = it->second;
	}
	return value;
}

template<typename T>
void	BitcoinExchange<T>::checkHeadline_(std::ifstream& file, const std::string& expectedHeadline) {
	std::string headline;
	std::getline(file, headline);
	if (headline != expectedHeadline) {
		throw std::invalid_argument(std::string("Incorrect headline in file! Expecting: '" + expectedHeadline + "'"));
	}
}

/*
	prints value of given amount of btc on given date
	(having multiplied it with the btc rate from stored data on that or lower date)
*/
template<typename T>
int	BitcoinExchange<T>::printCalculation_(year_month_day date, double amount) {
	if (amount > 0 && amount < 1000) {
		double	rate = selectValueFromData_(date);

		cout << int(date.year()) << "-"
			<< unsigned(date.month()) << "-"
			<< unsigned(date.day())
			<< " --> " << amount << " x " << rate
			<< " = " << rate * amount << endl;
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
void	BitcoinExchange<T>::errPrint_(std::string msg, std::string& line) {
	cout << BTC_RED << "Error: " << BTC_CLEAR << msg << " '"  << (line.length() > 42 ? line.substr(0, 39) + "..." : line) << "'" << endl;
}