/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grade.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:05:36 by bposa             #+#    #+#             */
/*   Updated: 2025/03/26 17:41:00 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRADE_HPP
# define GRADE_HPP

class Grade {
	unsigned short	_num;
public:
	Grade();
	Grade(const Grade& obj);
	Grade&	operator=(const Grade& obj);
	~Grade() = default;

	explicit Grade(unsigned short number);
	operator unsigned short() const;
};

#endif
