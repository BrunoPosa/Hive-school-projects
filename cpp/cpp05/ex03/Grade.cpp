/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grade.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:06:47 by bposa             #+#    #+#             */
/*   Updated: 2025/03/26 17:31:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Grade.hpp"

/*	Orthodox Canonical Form Members	*/

Grade::Grade() : _num(0) {}

Grade::Grade(const Grade& obj) : _num(obj._num) {}

Grade&	Grade::operator=(const Grade& obj) {
	if (this != &obj) {
		_num = obj._num;
	}
	return *this;
}


/*	Overloads	*/

Grade::Grade(unsigned short number) : _num(number) {}

Grade::operator unsigned short() const {
	return _num;
}
