/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:21:14 by bposa             #+#    #+#             */
/*   Updated: 2025/04/13 19:33:08 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>
#include <exception>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;

namespace {
	void	stack(void) {
		Data	data{"data", 42};

		uintptr_t	raw = Serializer::serialize(&data);
		Data*		copy = Serializer::deserialize(raw);

		cout << "------ stack ------" << "\n"
			<< "Original address of Data: " << &data << "\n"
			<< "Deserialized int to Data: " << copy << "\n"
			<< (copy == &data ?
					"\033[1;32m addresses equal. \033[0m"
				:	"\033[1;31m addresses different! \033[0m") << "\n"
			<< "copy's string: " << copy->s << ", number: " << copy->n << "\n"
			<<  "Raw serialized integer: " << raw << " (" << std::hex << raw << std::dec << ")" << endl;
	}

	void	heap(Data*& data) {
		data = new Data{"data", 42};

		uintptr_t	raw = Serializer::serialize(data);
		Data*		copy = Serializer::deserialize(raw);

		cout << "------ heap ------" << "\n"
			<< "Original address of Data: " << data << "\n"
			<< "Deserialized int to Data: " << copy << "\n"
			<< (copy == data ?
					"\033[1;32m addresses equal. \033[0m"
				:	"\033[1;31m addresses different! \033[0m") << "\n"
			<< "copy's string: " << copy->s << ", number: " << copy->n << "\n"
			<< "Raw serialized integer: " << raw << " (" << std::hex << raw << std::dec << ")" << endl;
	}
}
int main(void) {
	Data	*data = nullptr;
	try {
		stack();
		heap(data);
		delete data;
	} catch (std::exception& e) {
		cout << "\033[1;31m" << e.what() << "\033[0m" << endl;
		delete data;
		return 1;
	}
	return 0;
}
