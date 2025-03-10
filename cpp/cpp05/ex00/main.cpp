/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:06:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/10 15:22:28 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <memory>
#include <cstring>
#include <limits>

#define BUREAUCRATIC_NEW_FAILS_EVERY 10

static Bureaucrat* myNew(const Bureaucrat& b) {
	static unsigned int i = 0;
	if (++i == BUREAUCRATIC_NEW_FAILS_EVERY) {
		i = 0;
		throw std::bad_alloc();
	}
	return new Bureaucrat(b);
}

static bool  testConstructor() {
	cout << "------------------------------------" << endl;
	try {
		cout << 151 << endl;
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

static bool testUpGrade() {
	cout << "------------------------------------" << endl;
	try {
		Bureaucrat	Erin("Erin", 1);
		cout << Erin << endl;
		Erin.upGrade();
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
		cout << Jim << endl;
		Jim.downGrade();
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

static bool testNegativeGradesCorrectException() {
	cout << "------------------------------------" << endl;
	short correct = 0;
	try {
		Bureaucrat("Angela", -4);
	}
	catch (const std::exception& e) {
		if (strcmp(e.what(), "Grade too high!") == 0) {
			++correct;
		}
	}
	try {
		Bureaucrat("Angela", std::numeric_limits<long long>::max());
	}
	catch (const std::exception& e) {
		if (strcmp(e.what(), "Grade too low!") == 0) {
			++correct;
		}
	}
	try {
		Bureaucrat("Angela", std::numeric_limits<long long>::min());
	}
	catch (const std::exception& e) {
		if (strcmp(e.what(), "Grade too high!") == 0) {
			++correct;
		}
	}
	try {
		Bureaucrat("Angela", std::numeric_limits<int>::max());
	}
	catch (const std::exception& e) {
		if (strcmp(e.what(), "Grade too low!") == 0) {
			++correct;
		}
	}
	try {
		Bureaucrat("Angela", std::numeric_limits<int>::min());
	}
	catch (const std::exception& e) {
		if (strcmp(e.what(), "Grade too high!") == 0) {
			++correct;
		}
	}
	cout << "correct: " << correct << " of 5" << endl;
	return correct == 5;
}

static void testMallocFail() {
	cout << "------------------------------------" << endl;
	for (int i = 0; i < 10 * BUREAUCRATIC_NEW_FAILS_EVERY; ++i) {
		std::unique_ptr<Bureaucrat> ptr(myNew(Bureaucrat("Michael", 2)));
		// myNew(Bureaucrat("Michael", 2));
	}
}

int main () {
	try {
		cout << "------------------------------------" << endl;
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
		(testNegativeGradesCorrectException() == true) ?
				cout << MyColor::GREEN << "testNegativeGradesCorrectException() OK" << MyColor::RESET << endl
			:	cout << MyColor::RED << "testNegativeGradesCorrectException() KO" << MyColor::RESET << endl;
		cout << "------------------------------------" << endl;
		testMallocFail();
	}
	catch (std::exception& e) {
		cout << MyColor::YELLOW << e.what() << MyColor::RESET << endl;
	}
	catch (...) {
		cout << MyColor::YELLOW << "Unknown exception!" << MyColor::RESET << endl;
	}
	return 0;
}
