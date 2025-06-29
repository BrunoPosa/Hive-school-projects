/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:16:23 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 00:53:06 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include <string>
#include <iostream>
#include "ClapTrap.hpp"

using std::string;
using std::cout;
using std::endl;

class FragTrap : public ClapTrap
{
public:
    FragTrap();
    FragTrap(const FragTrap& obj);
    FragTrap&   operator=(const FragTrap& obj);
    ~FragTrap();
    FragTrap(const string& name);

    void    highFivesGuys();
};

#endif