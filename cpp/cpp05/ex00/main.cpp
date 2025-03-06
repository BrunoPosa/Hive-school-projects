/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:06:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/06 13:03:32 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <limits>

#define BUREAUCRATIC_LADDER 10

// static bool  testCreation() {
	
// 	return true;
// }

int main () {
	try {
		Bureaucrat a;
		Bureaucrat b("Stevey", 2);
		Bureaucrat c(b);
		cout << c << endl;
		// Bureaucrat *c = new Bureaucrat[std::numeric_limits<unsigned int>::max()];
		// c[1].getName();
		cout << a << b;
		for (int i = 0; i < BUREAUCRATIC_LADDER; i++){b.upGrade();}
		for (int i = 0; i < BUREAUCRATIC_LADDER; i++){a.downGrade();}
		cout << a << b;
	}
	catch (const std::exception& e) {
		cout << BUREAUCRATIC_YELLOW << e.what() << BUREAUCRATIC_COLOR_RESET << endl;
	}
	catch (...) {
		cout << BUREAUCRATIC_YELLOW << "Something else went wrong!" << BUREAUCRATIC_COLOR_RESET << endl;
	}
	return 0;
}
