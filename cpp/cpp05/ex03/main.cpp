/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:58 by bposa             #+#    #+#             */
/*   Updated: 2025/03/29 21:35:55 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	AForm* shrubbery = nullptr;
	AForm* robotomy = nullptr;
	AForm* presidential = nullptr;
	try {
		Intern randomIntern;

		cout << "=Valid form names:\n" << endl;
		shrubbery = randomIntern.makeForm("shrubbery creation", "Garden");
		robotomy = randomIntern.makeForm("robotomy request", "Bender");
		presidential = randomIntern.makeForm("presidential pardon", "Zaphod");
		cout << endl;
		Bureaucrat boss("Big Boss", 1);

		if (shrubbery) {
			boss.signForm(*shrubbery);
			boss.executeForm(*shrubbery);
			delete shrubbery;
		}
		cout << endl;
		if (robotomy) {
			boss.signForm(*robotomy);
			boss.executeForm(*robotomy);
			delete robotomy;
		}
		cout << endl;
		if (presidential) {
			boss.signForm(*presidential);
			boss.executeForm(*presidential);
			delete presidential;
		}

		cout << "-----------------------------------" << endl;
		cout << "=Invalid form name:" << endl;
		AForm* unknown = randomIntern.makeForm("unknown form", "Nobody");
		if (!unknown) {
			cout << "Intern failed to create an unknown form.\n";
		}
	} catch (const std::exception& e) {
		cout << "Exception caught: " << e.what() << endl;
		delete shrubbery;
		delete presidential;
		delete robotomy;
	}
	return 0;
}
