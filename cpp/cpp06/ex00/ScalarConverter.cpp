/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:23:23 by bposa             #+#    #+#             */
/*   Updated: 2025/04/06 16:57:16 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
//check if system char type is signed or unsigned
// #include <type_traits>
// if (std::is_signed<char>::value) {
// 	std::cout << "char is signed" << std::endl;
// } else {
// 	std::cout << "char is unsigned" << std::endl;
// }

using std::string;
using std::cout;
using std::endl;

namespace {

	void	_convertChar(unsigned int type, const string& lit, double *value);
	void	_convertInt(unsigned int type, const string& lit, double *value);
	void	_convertFloat(unsigned int type, const string& lit, double *value);
	void	_convertDouble(unsigned int type, const string& lit, double *value);

	enum _LiteralType { TYPE_CHAR, TYPE_INT, TYPE_FLOAT, TYPE_DOUBLE, TYPE_INVALID };

	void (*_typeConversionFunctions[4])(unsigned int type, const string& literal, double *value) = {
		_convertChar,
		_convertInt,
		_convertFloat,
		_convertDouble
	};

	bool	_hasValidChars(const string& lit) {
		if (lit.find_first_not_of("infa-+.0123456789") != string::npos) {
			return false;
		}

		return true;
	}

	_LiteralType	_assignType(const string& lit) {
		(void)lit;
		return TYPE_INVALID;
	}

	void	_convertChar(unsigned int type, const string& lit, double *value) {
		char	ch = 0;
		string	format = "char: ";
		bool	possible = true;

		if (type == TYPE_CHAR) {
			if (lit.length() == 3) { // "'c'"
				ch = lit.at(1);
			} else { // "c"
				ch = lit.at(0);
			}
		} else if (type < TYPE_INVALID) {
			if (*value <= std::numeric_limits<char>::max() && *value >= std::numeric_limits<char>::min()) {
				ch = static_cast<char>(*value);
			} else {
				possible = false;
			}
		}

		if (type == TYPE_INVALID || possible == false) {
			cout << format << "impossible!" << endl;
			return;
		} else if (ch < 32 || ch > 127) {
			cout << format << "Non displayable" << endl;
			return;
		}
		cout << format << "'" << ch << "'" << endl;
	}

	void	_convertInt(unsigned int type, const string& lit, double *value) {
		(void)type;
		(void)lit;
		(void)value;
		cout << "int: " << endl;
	}

	void	_convertFloat(unsigned int type, const string& lit, double *value) {
		(void)type;
		(void)lit;
		(void)value;
		cout << "float: " << endl;
	}

	void	_convertDouble(unsigned int type, const string& lit, double *value) {
		(void)type;
		(void)lit;
		(void)value;
		cout << "double: " << endl;
	}

}

/*
	-detect type of literal passed (char, int, float, double)
	-convert from string to the actual type
	-convert explicitly to the other 3 types
	-display the results
	-if conversion makes no sense or overflows, print impossible
	
*/
void	ScalarConverter::convert(const string& literal) {
	try {
		_LiteralType	type = TYPE_INVALID;
		double			value = 0;

		if (_hasValidChars(literal) == true) {
			type = _assignType(literal);
		}
		for (int i = 0; i < 4; i++) {
			(_typeConversionFunctions[(type + i) % 4])(type, literal, &value);
		}
	} catch (std::exception& e) {
		cout << YELLOWISH << "exception caugth: " << REDISH << e.what() << RESETISH << endl;
	}
	// float	nf2 = std::stof(literal, nullptr);
	// cout << "stof: " << nf2 << endl;
}