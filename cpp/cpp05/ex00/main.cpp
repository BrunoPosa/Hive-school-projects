/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:06:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/07 16:53:11 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Colors.hpp"
#include <cstdlib>

#define BUREAUCRATIC_LADDER 150
#define BUREAUCRATIC_NEW_FAILS_EVERY 2
#define BUREAUCRAT_NAME_MAX_LENGTH 10

class FaultyBureaucrat : public Bureaucrat {
public:
	FaultyBureaucrat() = default;
	FaultyBureaucrat(const string& name, long grade) : Bureaucrat(name, grade) {
		throw std::length_error("Name too long!");
	}
};

// static Bureaucrat* myNew(const Bureaucrat& b) {
// 	static unsigned int i = 0;
// 	cout << "i: " << i << endl;
// 	if (++i == BUREAUCRATIC_NEW_FAILS_EVERY) {
// 		i = 0;
// 		throw std::bad_alloc();
// 	}
// 	return new Bureaucrat(b);
// }

// static bool testBadAllocException() {
// 	cout << "------------------------------------" << endl;
// 	Bureaucrat* b = nullptr;
// 	b = myNew(Bureaucrat("Michael", 2));
// }

static bool  testConstructor() {
	cout << "------------------------------------" << endl;
	try {
		Bureaucrat	Kevin("Kevin", 151);
		cout << Kevin << endl;
	}
	catch (const std::exception& e) {
		cout << MyColor::YELLOW << e.what() << MyColor::RESET << endl;
		if (string(e.what()) == "Grade too low!") {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

static bool testTooLongName() {
	cout << "------------------------------------" << endl;
	try {
		FaultyBureaucrat	Michael("Michael", 2);
	}
	catch (const std::exception& e) {
		cout << MyColor::YELLOW << e.what() << MyColor::RESET << endl;
		return true;
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
		cout << MyColor::YELLOW << e.what() << MyColor::RESET << endl;
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
		cout << MyColor::YELLOW << e.what() << MyColor::RESET << endl;
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
	try {
		Bureaucrat h;
		Bureaucrat a;
		cout << "Class exception tests" << endl;
		(testConstructor() == true) ?
				cout << MyColor::GREEN << "testConstructor exception OK" << MyColor::RESET << endl
			:	cout << MyColor::RED << "testConstructor exception KO" << MyColor::RESET << endl;
		cout << "------------------------------------" << endl;
		(testUpGrade() == true) ?
				cout << MyColor::GREEN << "testUpGrade() exception OK" << MyColor::RESET << endl
			:	cout << MyColor::RED << "UpGrade() exception KO" << MyColor::RESET << endl;
		cout << "------------------------------------" << endl;
		(testDownGrade() == true) ?
				cout << MyColor::GREEN << "testDownGrade() exception OK" << MyColor::RESET << endl
			:	cout << MyColor::RED << "DownGrade() exception KO" << MyColor::RESET << endl;
		cout << "------------------------------------" << endl;
		(testTooLongName() == true) ?
				cout << MyColor::GREEN << "testTooLongName() exception OK" << MyColor::RESET << endl
			:	cout << MyColor::RED << "TooLongName() exception KO" << MyColor::RESET << endl;
		cout << "------------------------------------" << endl;

	}
	catch (std::exception& e) {
		cout << MyColor::YELLOW << e.what() << MyColor::RESET << endl;
	}
	catch (...) {
		cout << MyColor::YELLOW << "Unknown exception!" << MyColor::RESET << endl;
	}
	return 0;
}
