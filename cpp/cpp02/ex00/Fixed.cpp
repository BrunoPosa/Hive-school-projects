/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:16:23 by bposa             #+#    #+#             */
/*   Updated: 2025/01/31 17:43:42 by bposa            ###   ########.fr       */
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

Fixed::Fixed(const Fixed &obj) : _num(obj._num) {
	cout << "Copy constructor called." << endl;
};//why should you not use '=' in copy constructor?

Fixed& Fixed::operator=(const Fixed &obj) {
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