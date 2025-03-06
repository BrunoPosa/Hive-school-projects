/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:06:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/06 20:09:16 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Colors.hpp"

#include <limits>

#define BUREAUCRATIC_LADDER 150

static bool  testConstructor() {
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
	-make own new wrapper 
*/
int main () {
Bureaucrat *a = nullptr;
// Bureaucrat *c = nullptr;
	try {
		cout << "Class exception tests" << endl;
a = new Bureaucrat("John", 1);
(void)a;
		(testConstructor() == true) ?
				cout << getColor(Color::GREEN) << "testConstructor exception OK" << getColor(Color::RESET) << endl
			:	cout << getColor(Color::RED) << "testConstructor exception KO" << getColor(Color::RESET) << endl;

		(testUpGrade() == true) ?
				cout << getColor(Color::GREEN) << "testUpGrade() exception OK" << getColor(Color::RESET) << endl
			:	cout << getColor(Color::RED) << "UpGrade() exception KO" << getColor(Color::RESET) << endl;

		(testDownGrade() == true) ?
				cout << getColor(Color::GREEN) << "testDownGrade() exception OK" << getColor(Color::RESET) << endl
			:	cout << getColor(Color::RED) << "DownGrade() exception KO" << getColor(Color::RESET) << endl;

		// c = new Bureaucrat[std::numeric_limits<unsigned int>::max()];
		// c[1].getName();

		// for (int i = 0; i < BUREAUCRATIC_LADDER; i++){b.upGrade();}
		// for (int i = 0; i < BUREAUCRATIC_LADDER; i++){a.downGrade();}
		// cout << a << b;
		delete a;
		// delete[] c;
	}
	catch (...) {
		cout << getColor(Color::YELLOW) << "Something else went wrong!" << getColor(Color::RESET) << endl;
		delete a;
		// delete[] c;
	}
	return 0;
}
