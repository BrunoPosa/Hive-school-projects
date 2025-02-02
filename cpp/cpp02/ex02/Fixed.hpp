/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:16:14 by bposa             #+#    #+#             */
/*   Updated: 2025/02/02 12:44:27 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

class Fixed
{
	int					_num;
	static const int	_binpoint;

public:
	Fixed();
	Fixed(const Fixed &obj);
	Fixed&	operator=(const Fixed&);
	~Fixed();
	Fixed(const int n);
	Fixed(const float n);
	bool	operator<(const Fixed& obj) const;
	bool	operator>(const Fixed& obj) const;
	bool	operator<=(const Fixed& obj) const;
	bool	operator>=(const Fixed& obj) const;
	bool	operator==(const Fixed& obj) const;
	bool	operator!=(const Fixed& obj) const;
	Fixed	operator+(const Fixed& obj) const;

	int		getRawBits() const;
	void	setRawBits(int const raw);
	float	toFloat() const;
	int		toInt() const;
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif