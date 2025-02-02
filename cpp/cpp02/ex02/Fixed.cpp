/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:16:23 by bposa             #+#    #+#             */
/*   Updated: 2025/02/02 13:14:22 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

std::ostream&	operator<<(std::ostream& os, const Fixed& obj) {	return os << obj.toFloat();	}

const int Fixed::_binpoint = 8;



/*	Orthodox Canonical Form members	*/

Fixed::Fixed() : _num(0) {	cout << "Default constructor called." << endl;	}

Fixed::Fixed(const Fixed &obj) : _num(obj._num) {	cout << "Copy constructor called." << endl;	};

Fixed&	Fixed::operator=(const Fixed &obj) {
	cout << "Copy assignment operator called." << endl;
	if (this != &obj)
		this->_num = obj._num;
	return *this;
}

Fixed::~Fixed() {	cout << "Destructor called." << endl;	}



/*	Overloads	*/

Fixed::Fixed(const int n) : _num(n << _binpoint) {	cout << "Int constructor called." << endl;	}

Fixed::Fixed(const float n) : _num(static_cast<int>(roundf(n * (1 << _binpoint))))
{
	cout << "Float constructor called." << endl;
}

bool	Fixed::operator<(const Fixed& obj) const {	return this->_num < obj._num;	}

bool	Fixed::operator>(const Fixed& obj) const {	return this->_num > obj._num;	}

bool	Fixed::operator<=(const Fixed& obj) const {	return this->_num <= obj._num;	}

bool	Fixed::operator>=(const Fixed& obj) const {	return this->_num >= obj._num;	}

bool	Fixed::operator==(const Fixed& obj) const {	return this->_num == obj._num;	}

bool	Fixed::operator!=(const Fixed& obj) const {	return this->_num != obj._num;	}

Fixed	Fixed::operator+(const Fixed& obj) const {	 
	Fixed result;

	result._num = this->_num + obj._num;
	return result;
}//explain this well! can't be a one liner seemingly!


/*	member functions	*/

int		Fixed::getRawBits() const
{
	cout << "getRawBits member function called" << endl;
	return _num;
}

void	Fixed::setRawBits(int const raw)
{
	cout << "setRawBits member function called" << endl;
	_num = raw;
}

float	Fixed::toFloat() const {	return (static_cast<float>(_num) / (1 << _binpoint));	}

int		Fixed::toInt() const {	return _num >> _binpoint;	}
