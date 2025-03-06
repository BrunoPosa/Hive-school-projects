/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:06:52 by bposa             #+#    #+#             */
/*   Updated: 2025/03/06 18:07:03 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"

const char* getColor(Color c) {
	switch (c) {
		case Color::RED:	return "\033[1;31m";
		case Color::YELLOW:	return "\033[33m";
		case Color::GREEN:	return "\033[1;32m";
		default:			return "\033[0m";
	}
}
