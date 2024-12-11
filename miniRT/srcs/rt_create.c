/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:48:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/11 17:09:11 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
	allocates, fills and returns a new tuple, or NULL on errors.
	pass in VECTOR or POINT macro as 'w' parameter to specify the type of tuple.
*/
t_vec	create_vec(float x, float y, float z)
{
	t_vec	t;

	t.x = x;
	t.y = y;
	t.z = z;
	return (t);
}

// t_tuple *create_point(float x, float y, float z)
// {
// 	return (create_tuple(x, y, z, POINT));
// }

// t_tuple *create_vector(float x, float y, float z)
// {
// 	return (create_tuple(x, y, z, VECTOR));
// }

t_colour	create_colour(float r, float g, float b)
{
	t_colour	c;

	// if (r == 0)
	// 	r = EPSILON;
	// if (g == 0)
	// 	g = EPSILON;
	// if (b == 0)
	// 	b = EPSILON;
	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}
