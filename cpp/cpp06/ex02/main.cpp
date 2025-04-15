/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:02:33 by bposa             #+#    #+#             */
/*   Updated: 2025/04/15 21:35:56 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <exception>

using std::cout;
using std::endl;

namespace {

	Base* generate() {
		int choice = std::rand() % 3;

		switch (choice) {
			case 0: return new A();
			case 1: return new B();
			case 2: return new C();
			default: return nullptr;
		}
	}

	void identify(Base* p) {
		if (dynamic_cast<A*>(p))
			cout << "A" << endl;
		else if (dynamic_cast<B*>(p))
			cout << "B" << endl;
		else if (dynamic_cast<C*>(p))
			cout << "C" << endl;
	}

	void identify(Base& ref) {
		try {
			(void) dynamic_cast<A&>(ref);
			cout << "A" << endl;
			return;
		} catch (std::exception&) {}

		try {
			(void) dynamic_cast<B&>(ref);
			cout << "B" << endl;
			return;
		} catch (std::exception&) {}

		try {
			(void) dynamic_cast<C&>(ref);
			cout << "C" << endl;
			return;
		} catch (std::exception&) {}
	}
}

int main() {
	Base* instance = nullptr;

	try {
		std::srand(std::time(nullptr));

		instance = generate();
		cout << "Identify with pointer: " << endl;
		identify(instance);

		cout << "Identify with reference: " << endl;
		identify(*instance);

		delete instance;
	} catch (std::exception& e) {
		cout << "exception caught: " << e.what() << endl;
		delete instance;
		return 1;
	}

	return 0;
}
