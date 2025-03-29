/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:46 by bposa             #+#    #+#             */
/*   Updated: 2025/03/29 21:18:02 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <type_traits>
#include <memory>

using std::cout;
using std::endl;
using std::string;

static void	normalFormSignAndExecution() {
	cout << "=showing normal signing and execution of all 3 forms by boss (grade 1):\n" << endl;
	Bureaucrat boss("boss", 1);
	cout << boss << endl;
	{
		std::unique_ptr<AForm> p1(new ShrubberyCreationForm("Home"));
		boss.signForm(*p1);
		boss.executeForm(*p1);
	}
	{
		cout << endl;
		std::unique_ptr<AForm> p2(new RobotomyRequestForm("Rick"));
		boss.signForm(*p2);
		boss.executeForm(*p2);
	}
	{
		cout << endl;
		std::unique_ptr<AForm> p3(new PresidentialPardonForm("Proxima Centauri"));
		boss.signForm(*p3);
		boss.executeForm(*p3);
	}
}

static void	formSignExecuteGradeTooLow() {
	cout << "=showing signing and execution errors for all 3 forms by Ed (grade 150):\n" << endl;
	Bureaucrat ed("Ed", 150);
	cout << ed << endl;
	{
		std::unique_ptr<AForm> p1(new ShrubberyCreationForm("Home 2"));
		ed.signForm(*p1);
		ed.executeForm(*p1);
	}
	{
		cout << endl;
		std::unique_ptr<AForm> p2(new RobotomyRequestForm("Rick"));
		ed.signForm(*p2);
		ed.executeForm(*p2);
	}
	{
		cout << endl;
		std::unique_ptr<AForm> p3(new PresidentialPardonForm("Proxima Centauri"));
		ed.signForm(*p3);
		ed.executeForm(*p3);
	}
}

static void	formChecks() {
	cout << "=Forms checks\n" << endl;
	Bureaucrat	Frank("Frank", 3);
	cout << Frank << endl;
	ShrubberyCreationForm Form1("Form1");
	{
		Form1.beSigned(Frank);
		Form1.execute(Frank);
		Form1.act();
	}

}

int main (void) {
	try {
		cout << "======================= main =========================" << endl;
		static_assert(std::is_abstract<AForm>::value, "AForm must be an abstract class!");

		normalFormSignAndExecution();
		cout << "------------------------------------" << endl;
		formSignExecuteGradeTooLow();
		cout << "------------------------------------" << endl;
		formChecks();

	} catch (std::exception& e) {
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}
