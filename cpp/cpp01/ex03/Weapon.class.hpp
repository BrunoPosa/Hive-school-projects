/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:31:08 by bposa             #+#    #+#             */
/*   Updated: 2025/01/20 01:48:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_CLASS_HPP
# define WEAPON_CLASS_HPP

#include <iostream>
/* 
	the main practical difference between a struct and a class in cpp is its access control:
	-the struct has members public by default, inheriting also public by default
	-class has private by default, inheriting private as well. 
	Use struct when you primarily want a simple, data-holding object without requiring encapsulation
	or advanced features (although you can use access control and functions in structs.
	Use class when you want to define a more complex type with encapsulation, access control,
	or when you're implementing object-oriented features like inheritance or polymorphism.
*/
class Weapon
{
	std::string			_type;

public:
	Weapon(std::string type);

	const std::string&	getType() const;
	void				setType(std::string type);
};


#endif
