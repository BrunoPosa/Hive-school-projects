/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:23:23 by bposa             #+#    #+#             */
/*   Updated: 2025/04/10 18:11:48 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

using std::string;
using std::cout;
using std::endl;

namespace {

	void	_convertChar(unsigned int type, const string& lit, double *value);
	void	_convertInt(unsigned int type, const string& lit, double *value);
	void	_convertFloat(unsigned int type, const string& lit, double *value);
	void	_convertDouble(unsigned int type, const string& lit, double *value);

	enum _LiteralType {
		TYPE_CHAR = 0,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_INVALID
	};

	void (*_typeConversionFunctions[4])(unsigned int type, const string& literal, double *value) = {
		_convertChar,
		_convertInt,
		_convertFloat,
		_convertDouble
	};

	string	_toLower(const string& lit) {
		string	s = lit;

		for (char& ch : s) {
			if (ch >= 'A' && ch <= 'Z') {
				ch += ('a' - 'A');
			}
		}
		return s;
	}

	bool	_isSpecialDouble(const string& lit) {
		const string	specials[] = {"nan", "+nan", "-nan", "inf", "+inf", "-inf"};
		string			lowerLit = _toLower(lit);
	
		for (const string& s : specials) {
			if (lowerLit == s)
				return true;
		}
		return false;
	}

	bool	_isChar(const string& l) {
		size_t	len = l.length();

		if (len == 1
			&& !std::isdigit(l.at(0))) {
			return true;
		} else if (len == 3
			&& l.at(0) == '\''
			&& l.at(2) == '\'') {
				return true;
		}
		return false;
	}

	bool	_isInt(const string& l) {
		try {
			size_t pos;
			std::stoi(l, &pos);
			return (pos == l.length());
		} catch (std::exception& e) {
			return false;
		}
	}

	bool	_isFloat(const string& l) {
		try {
			if (_isSpecialDouble(l) || l.back() != 'f') {
				return false;
			}
			size_t pos;
			std::stof(l, &pos);
			return (pos == l.length() || (pos == l.length() - 1 && l.back() == 'f'));
		} catch (const std::exception& e) {
			return false;
		}
	}

	bool _isDouble(const string& lit) {
		try {
			size_t pos;
			std::stod(lit, &pos);
			return (pos == lit.length());
		} catch (const std::exception& e) {
			return false;
		}
	}

	_LiteralType	_assignType(const string& lit) {
		if (_isChar(lit) == true) {
			return TYPE_CHAR;
		} else if (lit.empty() || lit.find_first_not_of("infaINFA-+.0123456789") != string::npos) {
			return TYPE_INVALID;
		} else if (_isInt(lit) == true) {
			return TYPE_INT;
		} else if (_isFloat(lit) == true) {
			return TYPE_FLOAT;
		} else if (_isDouble(lit) == true) {
			return TYPE_DOUBLE;
		}
		return TYPE_INVALID;
	}

	void	_convertChar(unsigned int type, const string& lit, double *value) {
		char	ch = 0;
		bool	possible = true;

		if (type == TYPE_CHAR) {
			ch = (lit.length() == 3) ? lit.at(1) : lit.at(0);
			*value = static_cast<double>(ch);
		} else if (type != TYPE_INVALID) {
			if (*value <= std::numeric_limits<char>::max() && *value >= std::numeric_limits<char>::min()) {
				ch = static_cast<char>(*value);
			} else {
				possible = false;
			}
		}

		if (type == TYPE_INVALID || !possible) {
			cout << "char: impossible!" << endl;
		} else if (!std::isprint(ch)) {
			cout << "char: Non displayable!" << endl;
		} else {
			cout << "char: '" << ch << "'" << endl;
		}
	}

	void	_convertInt(unsigned int type, const string& lit, double *value) {
		int		n = 0;
		bool	possible = true;

		if (type == TYPE_INT) {
			n = std::stoi(lit);
			*value = static_cast<double>(n);
		} else if (type != TYPE_INVALID) {
			if (*value <= std::numeric_limits<int>::max() && *value >= std::numeric_limits<int>::min()) {
				n = static_cast<int>(*value);
			} else {
				possible = false;
			}
		}

		if (type == TYPE_INVALID || !possible) {
			cout << "int: impossible!" << endl;
		} else {
			cout << "int: " << n << endl;
		}
	}

	void	_convertFloat(unsigned int type, const string& lit, double *value) {
		float	f = 0.0f;
		bool	possible = true;

		if (type == TYPE_FLOAT) {
			f = std::stof(lit);
			*value = static_cast<double>(f);
		} else if (type != TYPE_INVALID) {
			if ((*value <= std::numeric_limits<float>::max() && *value >= std::numeric_limits<float>::lowest())
			|| _isSpecialDouble(lit)) {
				f = static_cast<float>(*value);
			} else {
				possible = false;
			}
		}

		if (type == TYPE_INVALID || !possible) {
			cout << "float: impossible!" << endl;
		} else {
			cout << "float: " << std::fixed << f << "f" << endl;
		}
	}

	void	_convertDouble(unsigned int type, const string& lit, double *value) {
		double	d = 0.0;

		if (type == TYPE_DOUBLE) {
			d = std::stod(lit);
			*value = d;
		} else if (type != TYPE_INVALID) {
			d = *value;
		}

		if (type == TYPE_INVALID) {
			cout << "double: impossible!" << endl;
		} else {
			cout << "double: " << std::fixed << d << endl;
		}
	}
}

void	ScalarConverter::convert(const string& literal) {
	try {
		double			value = 0;
		_LiteralType	type = _assignType(literal);

		for (int i = 0; i < 4; i++) {
			(_typeConversionFunctions[(type + i) % 4])(type, literal, &value);
		}
	} catch (std::exception& e) {
		cout << YELLOWISH << "exception caugth: " << REDISH << e.what() << RESETISH << endl;
	}
}
