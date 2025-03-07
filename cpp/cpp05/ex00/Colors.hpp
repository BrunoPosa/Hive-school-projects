/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:45:10 by bposa             #+#    #+#             */
/*   Updated: 2025/03/07 18:54:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
# define COLORS_HPP

class MyColor {
	MyColor() = delete;
public:
	static constexpr const char* RED	= "\033[1;31m";
	static constexpr const char* YELLOW	= "\033[33m";
	static constexpr const char* GREEN	= "\033[1;32m";
	static constexpr const char* RESET	= "\033[0m";
};

#endif
