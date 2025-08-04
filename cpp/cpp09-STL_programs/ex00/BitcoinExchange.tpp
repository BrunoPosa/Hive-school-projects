#include "BitcoinExchange.hpp"

template<typename T>
BitcoinExchange<T>::BitcoinExchange(T infile) : inputFile(infile) {

	std::cout << infile << std::endl;

	if (!inputFile.is_open()) {
		throw std::invalid_argument(strerror(errno));
	}


// while (std::getline(infile, line))
// {
// 	if (infile.eof() == false && infile.fail() == true) {
// 		return _printReturn(READING_ERROR, "error reading the file!");
// 	}
}


// template<typename T>
// bool	BitcoinExchange<T>::validate_(std::string& line) {
// 	std::cout << "validating.." << std::endl;



// }