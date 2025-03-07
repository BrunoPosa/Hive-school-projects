/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:06:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/07 14:26:34 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Colors.hpp"

#include <limits>

#define BUREAUCRATIC_LADDER 150
#define BUREAUCRATIC_NEW_DISASTER_EVERY 2

static Bureaucrat* myNew(const Bureaucrat& b) {
	static unsigned int i = 0;
	cout << "i: " << i << endl;
	if (++i == BUREAUCRATIC_NEW_DISASTER_EVERY) {
		i = 0;
		throw std::bad_alloc();
	}
	return new Bureaucrat(b);
}

// static bool testTwoExceptions() {
	
// }

static bool  testConstructor() {
	cout << "------------------------------------" << endl;
	try {
		Bureaucrat	Kevin("Kevin", 151);
		cout << Kevin << endl;
	}
	catch (const std::exception& e) {
		cout << getColor(Color::YELLOW) << e.what() << getColor(Color::RESET) << endl;
		if (string(e.what()) == "Grade too low!") {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

static bool testUpGrade() {
	cout << "------------------------------------" << endl;
	try {
		Bureaucrat	Erin("Erin", 1);
		Erin.upGrade();
		cout << Erin << endl;
	}
	catch (const std::exception& e) {
		cout << getColor(Color::YELLOW) << e.what() << getColor(Color::RESET) << endl;
		if (string(e.what()) == "Grade too high!") {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

static bool testDownGrade() {
	cout << "------------------------------------" << endl;
	try {
		Bureaucrat	Jim("Jim", 150);
		Jim.downGrade();
		cout << Jim << endl;
	}
	catch (const std::exception& e) {
		cout << getColor(Color::YELLOW) << e.what() << getColor(Color::RESET) << endl;
		if (string(e.what()) == "Grade too low!") {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

/*
	ToDo:
	DONE - make own new wrapper 
	-add myNew to test 2 exceptions in a 2nd level try catch 
*/
int main () {
Bureaucrat *a = nullptr;
Bureaucrat *v = nullptr;
// Bureaucrat *c = nullptr;
	try {
		cout << "Class exception tests" << endl;
a = myNew (Bureaucrat("John", 1));
v = myNew(Bureaucrat("Lucy", 21));
(void)v;
(void)a;

		(testConstructor() == true) ?
				cout << getColor(Color::GREEN) << "testConstructor exception OK" << getColor(Color::RESET) << endl
			:	cout << getColor(Color::RED) << "testConstructor exception KO" << getColor(Color::RESET) << endl;
		cout << "------------------------------------" << endl;
		(testUpGrade() == true) ?
				cout << getColor(Color::GREEN) << "testUpGrade() exception OK" << getColor(Color::RESET) << endl
			:	cout << getColor(Color::RED) << "UpGrade() exception KO" << getColor(Color::RESET) << endl;
		cout << "------------------------------------" << endl;
		(testDownGrade() == true) ?
				cout << getColor(Color::GREEN) << "testDownGrade() exception OK" << getColor(Color::RESET) << endl
			:	cout << getColor(Color::RED) << "DownGrade() exception KO" << getColor(Color::RESET) << endl;
		cout << "------------------------------------" << endl;

		// c = new Bureaucrat[std::numeric_limits<unsigned int>::max()];
		// c[1].getName();

		// for (int i = 0; i < BUREAUCRATIC_LADDER; i++){b.upGrade();}
		// for (int i = 0; i < BUREAUCRATIC_LADDER; i++){a.downGrade();}
		// cout << a << b;
		delete a;
		// delete[] c;
	}
	catch (std::exception& e) {//or (...)?
		cout << getColor(Color::YELLOW) << "Something else went wrong: " << e.what() << getColor(Color::RESET) << endl;
		delete a;
		delete v;
		// delete[] c;
	}
	return 0;
}
