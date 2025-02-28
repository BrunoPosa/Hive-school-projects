/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:20:09 by bposa             #+#    #+#             */
/*   Updated: 2025/02/28 23:30:48 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main(void)
{
{
	// cout << endl << "---- given main ----" << endl;
	// try {
	// 	const Animal* j = new Dog();
	// 	const Animal* i = new Cat();
	// 	delete j;//should not create a leak
	// 	delete i;
	// 	//...
	// 	return 0;
	// }
	// catch (const std::exception& e)
	// {
	// 	cout << e.what() << endl;
	// 	return 1;
	// }
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
		Bono.addIdea("Ice creamz");
		Dog bebe(Bono);
		// Bono = bebe;
		bebe.printIdeas();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}
}

