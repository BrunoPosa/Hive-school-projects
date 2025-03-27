/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:58 by bposa             #+#    #+#             */
/*   Updated: 2025/03/27 18:08:58 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

using std::cout;
using std::endl;
// using std::string;

int	main (void) {
	try {
		Intern someRandomIntern;
		Bureaucrat boss("Sam", 1);
		AForm* rrf;
		rrf = someRandomIntern.makeForm("robotomy REQUEST", "Bender");
		if (rrf) {
			boss.signForm(*rrf);
			boss.executeForm(*rrf);
		}
		delete rrf;
		Intern	newIntern(someRandomIntern);
	} catch (std::exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}
