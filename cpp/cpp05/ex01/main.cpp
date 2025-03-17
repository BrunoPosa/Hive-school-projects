/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:42:12 by bposa             #+#    #+#             */
/*   Updated: 2025/03/17 12:19:42 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <exception>

using std::cout;
using std::endl;

bool testValidFormCreation() {
	try {
		Form validForm("ValidForm", 50, 50);
		cout << validForm;
		if (validForm.getName() != "ValidForm")
			return false;
		if (validForm.getSignGrade() != 50)
			return false;
		if (validForm.getExecGrade() != 50)
			return false;
		if (validForm.getSigned() != false)
			return false;
	} catch (...) {
		return false;
	}
	return true;
}

bool testFormCreationTooHighSign() {
	try {
		Form invalidHigh("InvalidHigh", 0, 50);
	} catch (Form::GradeTooHighException& e) {
		cout << e.what() << endl;
		return true;
	} catch (...) {
		return false;
	}
	return false;
}

bool testFormCreationTooHighExecute() {
	try {
		Form invalidHigh("InvalidHigh", 10,-1);
	} catch (Form::GradeTooHighException& e) {
		cout << e.what() << endl;
		return true;
	} catch (...) {
		return false;
	}
	return false;
}


bool testFormCreationTooLow() {
	try {
		Form invalidLow("InvalidLow", 50, 151);
	} catch (Form::GradeTooLowException& e) {
		cout << e.what() << endl;
		return true;
	} catch (...) {
		return false;
	}
	return false;
}

bool testSuccessfulFormSigning() {
	try {
		Form signableForm("SignableForm", 100, 100);
		Bureaucrat highRank("HighRank", 50);
		highRank.signForm(signableForm);
		return signableForm.getSigned() == true;
	} catch (...) {
		return false;
	}
}

bool testUnsuccessfulFormSigning() {
	try {
		Form notSignableForm("NotSignableForm", 100, 100);
		Bureaucrat lowRank("LowRank", 150);
		lowRank.signForm(notSignableForm);
		return notSignableForm.getSigned() == false;
	// } catch (Form::GradeTooLowException& e) {
	// 	cout << e.what() << endl;
	// 	return true;
	} catch (...) {
		return false;
	}
}

int main() {
	int testsPassed = 0;
	int totalTests = 6;

	cout << "Running tests for Form and Bureaucrat classes:\n" << endl;

	if (testValidFormCreation()) {
		cout << GREENISH << "Test 1 (Valid Form Creation): OK" << RESETISH << endl;
		testsPassed++;
	} else {
		cout << "Test 1 (Valid Form Creation): KO" << endl;
	}

	if (testFormCreationTooHighSign()) {
		cout << GREENISH << "Test 2 (Form Creation with Too High Sign Grade): OK" << RESETISH << endl;
		testsPassed++;
	} else {
		cout << "Test 2 (Form Creation with Too High Grade): KO" << endl;
	}

	if (testFormCreationTooHighExecute()) {
		cout << GREENISH << "Test 3 (Form Creation with Too High Execute Grade): OK" << RESETISH << endl;
		testsPassed++;
	} else {
		cout << "Test 3 (Form Creation with Too High Grade): KO" << endl;
	}

	if (testFormCreationTooLow()) {
		cout << GREENISH << "Test 4 (Form Creation with Too Low Grade): OK" << RESETISH << endl;
		testsPassed++;
	} else {
		cout << "Test 4 (Form Creation with Too Low Grade): KO" << endl;
	}

	if (testSuccessfulFormSigning()) {
		cout << GREENISH << "Test 5 (Successful Form Signing): OK" << RESETISH << endl;
		testsPassed++;
	} else {
		cout << "Test 5 (Successful Form Signing): KO" << endl;
	}

	if (testUnsuccessfulFormSigning()) {
		cout << GREENISH << "Test 6 (Unsuccessful Form Signing due to Low Bureaucrat Grade): OK" << RESETISH << endl;
		testsPassed++;
	} else {
		cout << "Test 6 (Unsuccessful Form Signing due to Low Bureaucrat Grade): KO" << endl;
	}

	cout << "\n" << testsPassed << " out of " << totalTests << " tests passed." << endl;
	return (testsPassed == totalTests) ? 0 : 1;
}
