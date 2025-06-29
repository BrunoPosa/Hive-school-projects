/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:00:26 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 00:54:20 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(void)
{
	try
	{
		Harl	Harly;

		Harly.complain("HELLO");
		Harly.complain("INFO");
		Harly.complain("DEBUG ");
		Harly.complain("DEBUG");
		Harly.complain(nullptr);

	}
	catch(const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}