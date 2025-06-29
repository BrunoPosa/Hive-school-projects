/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:20:09 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 23:35:11 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main(void)
{
{
	cout << endl << "---- given main + array of 100 animals ----" << endl;
	try {
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		delete j;//should not create a leak
		delete i;
		//...

		Animal* zoo[100];
		for (int k = 0; k < 50; k++) {
			zoo[k] = new Dog();
		}
		for (int k = 50; k < 100; k++) {
			zoo[k] = new Cat();
		}
		for (Animal *animal : zoo) {
			animal->addIdea("om nom");
			animal->makeSound();
			animal->printIdeas();
		}
		for (Animal *animal : zoo) {
			delete animal;
		}
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
		cout << "\e[33m" << "Brains:" << "\e[0m" << endl;
		Brain a;
		a.addIdea("eat");
		a.addIdea("sleep");
		a.addIdea("poop");
		a.addIdea("repeat");
		Brain b(a);
		b.addIdea("dance monkey");
		Brain c;
		c = b;
		c.addIdea("RANDOM");
		a.printAll();
		cout << endl;
		b.printAll();
		cout << endl;
		c.printAll();

		cout << endl << endl;
		cout << "\e[33m" << "Dogs:" << "\e[0m" << endl;
		Dog Bono;
		Bono.addIdea("Food");
		Dog bebe(Bono);
		bebe.addIdea("Ice creamz");
		Dog Fifi;
		Fifi = bebe;
		Fifi.addIdea("Fluff");
		Bono.printIdeas();
		cout << endl;
		bebe.printIdeas();
		cout << endl;
		Fifi.printIdeas();
		Fifi.makeSound();

		cout << endl << endl;
		cout << "\e[33m" << "Cats:" << "\e[0m" << endl;
		Cat Donna;
		Donna.addIdea("Food");
		Cat bob(Donna);
		bob.addIdea("Ice creamz");
		Cat Fee;
		Fee = bob;
		Fee.addIdea("Fluff");
		Donna.printIdeas();
		cout << endl;
		bob.printIdeas();
		cout << endl;
		Fee.printIdeas();
		Fee.makeSound();

		WrongCat test;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}
	return 0;
}
