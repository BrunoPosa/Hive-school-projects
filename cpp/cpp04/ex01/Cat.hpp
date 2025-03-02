/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:23:26 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 21:26:50 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"
#include "Brain.hpp"

using std::string;
using std::cout;
using std::endl;

class Cat : public Animal
{
	Brain	*_brain;

public:
	Cat();
	Cat(const Cat& obj);
	Cat&	operator=(const Cat& obj);
	~Cat();

	void	makeSound() const override;
	void	addIdea(const string& idea) override;
	void	printIdeas() const override;
};

#endif