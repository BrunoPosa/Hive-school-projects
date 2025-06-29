/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:13:51 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 18:16:22 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class WrongAnimal
{
protected:
	string  _type;

public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal& obj);
	WrongAnimal&	operator=(const WrongAnimal& obj);
	virtual ~WrongAnimal();

	void	makeSound() const;
	string	getType() const;
};

#endif