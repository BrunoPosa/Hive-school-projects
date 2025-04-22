/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:58:01 by bposa             #+#    #+#             */
/*   Updated: 2025/04/21 21:37:33 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
// #include <filesystem>
// #include <string_view>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <locale>
#include <cassert>

using std::string;
using std::cerr;
using std::cout;
using std::endl;

int main()
{
	try {
		Socket  a;
		assert(a.getFd() == 5);
		(void)a;

		return 0;

	} catch (const std::system_error& e) {
		cerr << e.what() << ": " << e.code().message() << endl;
		return -1;
	} catch (std::exception& e) {
		cerr << e.what() << endl;
		return -1;
	}
}
