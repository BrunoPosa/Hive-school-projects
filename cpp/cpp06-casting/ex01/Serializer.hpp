/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:05:43 by bposa             #+#    #+#             */
/*   Updated: 2025/04/13 16:12:16 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include "Data.hpp"
#include <string>
#include <cstdint>

class Serializer {
	Serializer()									= delete;
	Serializer(const Serializer& obj)				= delete;
	Serializer &operator=(const Serializer& obj)	= delete;
	~Serializer()									= delete;
	
	public:
		static uintptr_t	serialize(Data* ptr);
		static Data*		deserialize(uintptr_t raw);
};

#endif
