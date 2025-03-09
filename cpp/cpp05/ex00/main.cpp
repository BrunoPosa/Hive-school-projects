/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:06:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/09 22:27:18 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
// #include "Colors.hpp"
#include <cstdlib>
#include <memory>
#include <limits>

#define BUREAUCRATIC_LADDER 150
#define BUREAUCRATIC_NEW_FAILS_EVERY 5

class FaultyBureaucrat : public Bureaucrat {
public:
	FaultyBureaucrat() = default;
	FaultyBureaucrat(const string& name, long grade) : Bureaucrat(name, grade) {
		static int i = 0;
		cout << "i: " << i << endl;
		if (++i == BUREAUCRATIC_NEW_FAILS_EVERY) {
			i = 0;
			throw std::bad_alloc();
		}
		// throw std::length_error("Name too long!");
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
		std::unique_ptr<FaultyBureaucrat> p1(new FaultyBureaucrat());
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

// static bool testWrapAroundGradeCorrectException() {
// 	cout << "------------------------------------" << endl;
// 	int	i = 0;
// 	try {
// 		Bureaucrat("Angela", -1);
// 	}
// 	catch (const std::exception& e) {
// 		if (string(e.what()) == "Grade too high!") {
// 			++i;
// 		}
// 	}
// 	catch (const std::exception& e) {
// 		cout << MyColor::YELLOW << e.what() << MyColor::RESET << endl;
// 		if (i == 4) {
// 			return true;
// 		}
// 	}
// 	return false;
// }

/*
	ToDo:
	DONE - make own new wrapper 
	-add myNew to test 2 exceptions in a 2nd level try catch 
*/
int main () {
	try {
		Bureaucrat h("Howard", -2147483649);
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
