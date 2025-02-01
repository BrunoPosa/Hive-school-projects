/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:16:23 by bposa             #+#    #+#             */
/*   Updated: 2025/02/01 13:43:44 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int Fixed::_binpoint = 8;

Fixed::Fixed() : _num(0) {
	cout << "Default constructor called." << endl;
}

Fixed::~Fixed() {
	cout << "Destructor called." << endl;
}

Fixed::Fixed(const int n) : _num(n) {
	cout << "Int constructor called." << endl;
	_num = _num << _binpoint;
}

Fixed::Fixed(const float n) :
	_num(static_cast<int>(roundf(n * (1 << _binpoint)))) {
	cout << "Float constructor called." << endl;
}

Fixed::Fixed(const Fixed &obj) : _num(obj._num) {
	cout << "Copy constructor called." << endl;
};

Fixed&	Fixed::operator=(const Fixed &obj) {
	cout << "Copy assignment operator called." << endl;
	if (this != &obj)
		this->_num = obj._num;
	return *this;
}

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
//printed result does not look like in the subject example!

float	Fixed::toFloat() const {
	return static_cast<float>(_num) * 1 / (1 << _binpoint);
}

int		Fixed::toInt() const {
	return _num >> _binpoint;
}

std::ostream&	operator<<(std::ostream& os, const Fixed& obj)
{
	os << obj.toFloat();
	return os;
}
