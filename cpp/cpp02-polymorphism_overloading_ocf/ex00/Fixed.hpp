/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:16:14 by bposa             #+#    #+#             */
/*   Updated: 2025/02/05 16:20:39 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

using std::cout;
using std::endl;

class Fixed
{
	int					_num;
	static const int	_fracBits;

public:
	Fixed();
	Fixed(const Fixed &obj);
	Fixed& operator=(const Fixed&);
	~Fixed();

	int		getRawBits() const;
	void	setRawBits(int const raw);
};

#endif