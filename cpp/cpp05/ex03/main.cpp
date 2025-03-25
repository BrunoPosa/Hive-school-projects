/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:58 by bposa             #+#    #+#             */
/*   Updated: 2025/03/25 17:01:54 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

int	main (void) {

	Intern someRandomIntern;
	Bureaucrat boss("Sam", 1);
	AForm* rrf;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	boss.signForm(*rrf);
	boss.executeForm(*rrf);
	delete rrf;
	return 0;
}
