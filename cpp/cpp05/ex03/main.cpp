/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:58 by bposa             #+#    #+#             */
/*   Updated: 2025/03/25 13:52:37 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

int	main (void) {

	Intern someRandomIntern;
	Bureaucrat boss("Sam", 1);
	AForm* rrf;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	boss.executeForm(*rrf);
	return 0;
}
