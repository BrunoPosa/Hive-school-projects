/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:46 by bposa             #+#    #+#             */
/*   Updated: 2025/03/23 18:25:19 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	-test the virtual destruction (e.g. use heap and cheack for leaks)
*/
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <type_traits>
#include <memory>

static void	showVirtualDestructor() {
	std::unique_ptr<AForm> p(new ShrubberyCreationForm());
}

int main (void) {
	static_assert(std::is_abstract<AForm>::value, "AForm must be an abstract class!");

	showVirtualDestructor();

	std::shared_ptr<AForm> ptr(new ShrubberyCreationForm("Hello"));

	Bureaucrat boss("boss", 3);
	boss.signForm(*ptr);
	if (ptr->execute(boss) == true)
	{cout << "true" << endl;}
}