/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:16:23 by bposa             #+#    #+#             */
/*   Updated: 2025/02/02 12:10:21 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int Fixed::_binpoint = 8;

/*	Orthodox Canonical Form members	*/

Fixed::Fixed() : _num(0) {
	cout << "Default constructor called." << endl;
}

Fixed::Fixed(const Fixed &obj) : _num(obj._num) {
	cout << "Copy constructor called." << endl;
};

Fixed& Fixed::operator=(const Fixed &obj) {
	cout << "Copy assignment operator called." << endl;
	if (this != &obj) {
		this->_num = obj._num;
	}
	getRawBits();
	return *this;
}

Fixed::~Fixed() {
	cout << "Destructor called." << endl;
}

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
