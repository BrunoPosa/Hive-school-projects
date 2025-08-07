#include "BitcoinExchange.hpp"

using std::string;
using std::cout;
using std::endl;

template<typename T>
BitcoinExchange<T>::BitcoinExchange(T input) : datafile_{BTC_DATAFILE}, infile_{input} {

	if (!datafile_.is_open() || !infile_.is_open()) {
		throw std::invalid_argument("Could not open infile or datafile: " + string(strerror(errno)));
	}

	for (string line; std::getline(infile_, line); ) {
		if (isValidDate_(line) == true) {
			cout << line << endl;
		} else {
			cout << "Error with input: " << line << endl;
		}
	}

}

template<typename T>
bool	BitcoinExchange<T>::isValidDate_(const std::string& line) {

	return parseDate_(line.substr(0, line.find(" ")))
		.ok();
}

template<typename T>
std::chrono::year_month_day	BitcoinExchange<T>::parseDate_(const std::string& date) {
    std::istringstream	iss(date);
    int y{};
	unsigned int m{}, d{};
	char dash{};

    if ((iss >> y >> dash >> m >> dash >> d) && iss.eof()) {
        return std::chrono::year{y}/std::chrono::month{m}/std::chrono::day{d};
    }
    return std::chrono::year_month_day{};
}
