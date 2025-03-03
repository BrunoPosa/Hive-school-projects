/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:20:09 by bposa             #+#    #+#             */
/*   Updated: 2025/03/03 16:55:32 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main(void)
{
{
	cout << endl << "---- given main ----" << endl;
	try {
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();
		delete meta;
		delete j;
		delete i;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}
{
	cout << endl << "---- given main with WrongCat : WrongAnimal ----" << endl << endl;
	try {
		const WrongAnimal* meta = new WrongAnimal();
		const Animal* j = new Dog();
		const WrongAnimal* i = new WrongCat();
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();
		delete meta;
		delete j;
		delete i;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}
{
	try {
		cout << endl << "---- custom tests ----" << endl << endl;
		Animal	*og = new Dog();
		og->makeSound();
		Dog Ruff;
		Dog	*GoodBoy = new Dog(Ruff);
		Dog Puff;
		Puff = Ruff;
		GoodBoy->makeSound();
		cout << GoodBoy->getType() << endl;
		delete og;
		delete GoodBoy;

		cout << endl << endl;
		Cat kit;
		Cat kat;
		kit = kat;
		Cat moo(kit);
		cout << kit.getType() << endl;
		kat.makeSound();

		cout << endl << endl;
		Animal	animal;
		animal.makeSound();
		cout << "animal type: " << animal.getType() << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}
	return 0;
}
