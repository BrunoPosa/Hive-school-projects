/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:46 by bposa             #+#    #+#             */
/*   Updated: 2025/03/27 18:19:59 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <type_traits>
#include <memory>

static void	showVirtualDestructor() {
	cout << "showing virtual destructor:" << endl;
	std::unique_ptr<AForm> p(new ShrubberyCreationForm());
}

static void	normalFormSignAndExecution() {
	cout << "showing normal signing and execution by boss (grade 1):" << endl;
	Bureaucrat boss("boss", 1);

	std::unique_ptr<AForm> p1(new ShrubberyCreationForm("Home"));
	boss.signForm(*p1);
	boss.executeForm(*p1);
	std::unique_ptr<AForm> p2(new RobotomyRequestForm("Rick"));
	boss.signForm(*p2);
	boss.executeForm(*p2);
	std::unique_ptr<AForm> p3(new PresidentialPardonForm("Proxima Centauri"));
	boss.signForm(*p3);
	boss.executeForm(*p3);
}

static void	formSignError() {
	cout << "showing signing errors:" << endl;
	Bureaucrat ed("Ed", 150);

	std::unique_ptr<AForm> p1(new ShrubberyCreationForm("Home"));
	ed.signForm(*p1);
	// boss.executeForm(*p1);
	// std::unique_ptr<AForm> p2(new RobotomyRequestForm("Rick"));
	// boss.signForm(*p2);
	// boss.executeForm(*p2);
	// std::unique_ptr<AForm> p3(new PresidentialPardonForm("Proxima Centauri"));
	// boss.signForm(*p3);
	// boss.executeForm(*p3);
}

/*
	-add noexcept guarantees around
	- update all other classes in ex02 (apart from AForm), 01, and 00 to reflect ex03
*/
int main (void) {
	try {
		cout << "======================= main =========================" << endl;
		static_assert(std::is_abstract<AForm>::value, "AForm must be an abstract class!");

		showVirtualDestructor();
		cout << "------------------------------------" << endl;
		normalFormSignAndExecution();
		cout << "------------------------------------" << endl;
		formSignError();

	} catch (std::exception& e) {
		cout << e.what() << endl;
	}
}