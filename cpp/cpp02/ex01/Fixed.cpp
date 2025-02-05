/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:16:23 by bposa             #+#    #+#             */
/*   Updated: 2025/02/05 16:20:39 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

std::ostream&	operator<<(std::ostream& os, const Fixed& obj)
{
	os << obj.toFloat();
	return os;
}

const int	Fixed::_fracBits = 8;



/*	Orhtodox Canonical Form members	*/

Fixed::Fixed() : _num(0) {	cout << "Default constructor called." << endl;	}

Fixed::Fixed(const Fixed &obj) : _num(obj._num)
{
	cout << "Copy constructor called." << endl;
};

Fixed&	Fixed::operator=(const Fixed &obj) {
	cout << "Copy assignment operator called." << endl;
	if (this != &obj) {
		this->_num = obj._num;
	}
	return *this;
}

Fixed::~Fixed() {	cout << "Destructor called." << endl;	}



/*	Overloads	*/

Fixed::Fixed(const int n) : _num(n << _fracBits)
{
	cout << "Int constructor called." << endl;
}

Fixed::Fixed(const float n) : _num(static_cast<int>(roundf(n * (1 << _fracBits))))
{
	cout << "Float constructor called." << endl;
}



/*	Member functions	*/

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

float	Fixed::toFloat() const
{
	return static_cast<float>(_num) / (1 << _fracBits);
}

int		Fixed::toInt() const
{
	return _num >> _fracBits;
}
