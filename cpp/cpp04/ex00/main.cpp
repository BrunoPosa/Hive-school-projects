/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:20:09 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 20:46:15 by bposa            ###   ########.fr       */
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
		Animal	GoodBoy(*og);
		GoodBoy.makeSound();
		GoodBoy = Cat();
		cout << GoodBoy.getType() << endl;
		GoodBoy.makeSound();
		delete og;

		cout << endl << endl;
		Cat	*kit = new Cat();
		og = kit;
		cout << og->getType() << endl;
		og->makeSound();
		delete og;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}
{
    try {
        cout << "---- Testing Polymorphism and Virtual Destructor ----" << endl;
        // Test 1: Base pointer to derived object
        Animal* zoo[2];
        zoo[0] = new Dog();
        zoo[1] = new Cat();
        for (int i = 0; i < 2; i++) {
            cout << "Type: " << zoo[i]->getType() << " | ";
            zoo[i]->makeSound();
            delete zoo[i];  // Virtual destructor ensures proper cleanup
        }
        cout << endl;

        cout << "---- Testing Copy Construction ----" << endl;
        // Test 2: Copy a derived object through base type
        Dog originalDog;
        Animal copiedDog(originalDog);  // Slicing happens here, intentional
        cout << "Original: ";
        originalDog.makeSound();
        cout << "Copied (base): ";
        copiedDog.makeSound();  // Should use Animal's makeSound due to slicing
        cout << endl;

        cout << "---- Testing Assignment and Type Preservation ----" << endl;
        // Test 3: Assignment between base and derived
        Animal baseAnimal;
        Cat kitty;
        baseAnimal = kitty;  // Assign derived to base, slicing occurs
        cout << "Assigned base type: " << baseAnimal.getType() << " | ";
        baseAnimal.makeSound();  // Animal sound, not Cat sound
        cout << "Original kitty: ";
        kitty.makeSound();  // Still a Cat
        cout << endl;

        cout << "---- Testing Deep Polymorphism ----" << endl;
        // Test 4: Pointer reassignment and dynamic behavior
        Animal* pet = new Dog();
        cout << "Pet as Dog: ";
        pet->makeSound();
        delete pet;
        pet = new Cat();
        cout << "Pet as Cat: ";
        pet->makeSound();
        delete pet;
        cout << endl;

        cout << "---- Testing Const Correctness ----" << endl;
        // Test 5: Const object with virtual method
        const Dog constantDog;
        cout << "Const Dog type: " << constantDog.getType() << " | ";
        constantDog.makeSound();  // Works because makeSound() is const
    }
    catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
        return 1;
    }
    cout << "---- All tests completed ----" << endl;
}
	return 0;
}
