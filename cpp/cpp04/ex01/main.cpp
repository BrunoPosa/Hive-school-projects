/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:20:09 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 20:30:43 by bposa            ###   ########.fr       */
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
		// Brain a;
		// a.addIdea("Helsinki");
		// a.addIdea("Poop");
		// a.addIdea("Grr");
		// a.addIdea("Boo");
		// a.printAll();
		// Brain b;
		// b = a;
		// b.printAll();
		Dog Bono;
		Bono.addIdea("Food");
		Dog bebe(Bono);
		bebe.addIdea("Ice creamz");
		// Bono = bebe;
		Bono.printIdeas();
		bebe.printIdeas();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}
	return 0;
}
