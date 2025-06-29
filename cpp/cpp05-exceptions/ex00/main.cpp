/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:06:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/31 17:17:59 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <memory>
#include <cstring>
#include <limits>

#define BUREAUCRATIC_NEW_FAILS_EVERY 10

#ifndef REDISH
# define REDISH "\033[1;31m"
#endif
#ifndef YELLOWISH
# define YELLOWISH "\033[33m"
#endif
#ifndef GREENISH
# define GREENISH "\033[1;32m"
#endif
#ifndef RESETISH
# define RESETISH "\033[0m"
#endif

using std::cout;
using std::endl;
using std::string;

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
		cout << YELLOWISH << e.what() << RESETISH << endl;
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
		cout << YELLOWISH << e.what() << RESETISH << endl;
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
		cout << YELLOWISH << e.what() << RESETISH << endl;
		if (string(e.what()) == "Grade too low!") {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

// static bool testNegativeGradesCorrectException() {
// 	cout << "------------------------------------" << endl;
// 	short correct = 0;
// 	try {
// 		Bureaucrat("Angela", -4);
// 	}
// 	catch (const std::exception& e) {
// 		if (strcmp(e.what(), "Grade too high!") == 0) {
// 			++correct;
// 		}
// 	}
// 	try {
// 		Bureaucrat("Angela", std::numeric_limits<long long>::max());
// 	}
// 	catch (const std::exception& e) {
// 		if (strcmp(e.what(), "Grade too low!") == 0) {
// 			++correct;
// 		}
// 	}
// 	try {
// 		Bureaucrat("Angela", std::numeric_limits<long long>::min());
// 	}
// 	catch (const std::exception& e) {
// 		if (strcmp(e.what(), "Grade too high!") == 0) {
// 			++correct;
// 		}
// 	}
// 	try {
// 		Bureaucrat("Angela", std::numeric_limits<int>::max());
// 	}
// 	catch (const std::exception& e) {
// 		if (strcmp(e.what(), "Grade too low!") == 0) {
// 			++correct;
// 		}
// 	}
// 	try {
// 		Bureaucrat("Angela", std::numeric_limits<int>::min());
// 	}
// 	catch (const std::exception& e) {
// 		if (strcmp(e.what(), "Grade too high!") == 0) {
// 			++correct;
// 		}
// 	}
// 	cout << "correct: " << correct << " of 5" << endl;
// 	return correct == 5;
// }

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
				cout << GREENISH << "testConstructor exception OK" << RESETISH << endl
			:	cout << REDISH << "testConstructor exception KO" << RESETISH << endl;
		cout << "------------------------------------" << endl;
		(testUpGrade() == true) ?
				cout << GREENISH << "testUpGrade() exception OK" << RESETISH << endl
			:	cout << REDISH << "UpGrade() exception KO" << RESETISH << endl;
		cout << "------------------------------------" << endl;
		(testDownGrade() == true) ?
				cout << GREENISH << "testDownGrade() exception OK" << RESETISH << endl
			:	cout << REDISH << "DownGrade() exception KO" << RESETISH << endl;
		cout << "------------------------------------" << endl;
		/*[obsolete]*/
		// (testNegativeGradesCorrectException() == true) ?
		// 		cout << GREENISH << "testNegativeGradesCorrectException() OK" << RESETISH << endl
		// 	:	cout << REDISH << "testNegativeGradesCorrectException() KO" << RESETISH << endl;
		cout << "------------------------------------" << endl;
		testMallocFail();
	}
	catch (std::exception& e) {
		cout << "Main catch: " << YELLOWISH << e.what() << RESETISH << endl;
	}
	catch (...) {
		cout << YELLOWISH << "Unknown exception!" << RESETISH << endl;
		return 1;
	}
	return 0;
}
