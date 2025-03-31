/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:58 by bposa             #+#    #+#             */
/*   Updated: 2025/03/31 17:03:33 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

using std::cout;
using std::endl;
using std::unique_ptr;

int main() {
	try {
		Intern randomIntern;
		Bureaucrat boss("Big Boss", 1);
		Bureaucrat clerk("Joe", 137);
		{
			cout << "-----------------------------------" << endl;
			cout << "=Valid form names:\n" << endl;
			unique_ptr<AForm> shrubbery = randomIntern.makeForm("shrubbery creation", "Garden");
			unique_ptr<AForm> robotomy = randomIntern.makeForm("robotomy request", "Bender");
			unique_ptr<AForm> presidential = randomIntern.makeForm("presidential pardon", "Zaphod");
			cout << endl;

			if (shrubbery) {
				boss.signForm(*shrubbery);
				boss.executeForm(*shrubbery);
			}
			cout << endl;
			if (robotomy) {
				boss.signForm(*robotomy);
				boss.executeForm(*robotomy);
				clerk.executeForm(*robotomy);
			}
			cout << endl;
			if (presidential) {
				boss.signForm(*presidential);
				boss.executeForm(*presidential);
			}
		}
		{
			cout << "-----------------------------------" << endl;
			cout << "=Invalid form name:\n" << endl;
			unique_ptr<AForm> unknown = randomIntern.makeForm("unknown Form", "Nobody");
		}
		{
			try {
				cout << "-----------------------------------" << endl;
				cout << "=Invalid shrubbery target:\n" << endl;
				unique_ptr<AForm>	illegalTarget = randomIntern.makeForm("shrubbery creation", "space space[!]");
				boss.signForm(*illegalTarget);
			} catch (std::invalid_argument& e) {
				cout << YELLOWISH << e.what() << RESETISH << endl;
			}
		}
		{
			try {
				cout << "-----------------------------------" << endl;
				cout << "=Another invalid shrubbery target:\n" << endl;
				unique_ptr<AForm>	illegalTarget = randomIntern.makeForm("shrubbery creation", "Looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo0ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
				boss.signForm(*illegalTarget);
			} catch (std::invalid_argument& e) {
				cout << YELLOWISH << e.what() << RESETISH << endl;
			}
		}
		{
			cout << "-----------------------------------" << endl;
			cout << "=OCF Intern:\n" << endl;
			Intern joe(randomIntern);
			joe = randomIntern;
		}
	} catch (const std::exception& e) {
		cout << "Main catch: " << YELLOWISH << e.what() << RESETISH << endl;
	}
	return 0;
}
