/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:46 by bposa             #+#    #+#             */
/*   Updated: 2025/03/23 21:17:51 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	-test the virtual destruction (e.g. use heap and cheack for leaks)
*/
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <type_traits>
#include <memory>

static void	showVirtualDestructor() {
	std::unique_ptr<AForm> p(new ShrubberyCreationForm());
}

int main (void) {
	static_assert(std::is_abstract<AForm>::value, "AForm must be an abstract class!");

	showVirtualDestructor();

	std::unique_ptr<AForm> p1(new ShrubberyCreationForm("Hello"));

	Bureaucrat boss("boss", 3);
	boss.signForm(*p1);
	if (p1->execute(boss) == true)	{
		cout << "p1 true" << endl;
	}
	std::unique_ptr<AForm> p2(new RobotomyRequestForm("Zidane"));
	boss.signForm(*p2);
	if (p2->execute(boss) == true) {
		cout << "p2 true" << endl;
	}

	std::unique_ptr<AForm> p3(new PresidentialPardonForm("Myself and I"));
	boss.signForm(*p3);
	p3->execute(boss);
}