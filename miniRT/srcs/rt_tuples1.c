/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tuples1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:52:19 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
	returns a tuple with each member divided, or same tuple if divisor is 0
*/
t_vec	divide_tuple(t_vec t, float divisor)
{
	t_vec	res;

	if (divisor == 0)
		return (t);
	res.x = t.x / divisor;
	res.y = t.y / divisor;
	res.z = t.z / divisor;
	return (res);
}

float	magnitude(t_vec t)
{
	return (sqrt(t.x * t.x + t.y * t.y + t.z * t.z));
}

/*
	returns the normalized input vector
*/
t_vec	normalize(t_vec t)
{
	t_vec	res;
	float	mag;

	mag = magnitude(t);
	res.x = t.x / mag;
	res.y = t.y / mag;
	res.z = t.z / mag;
	return (res);
}

/*
	returns dot product of two vectors
*/
float	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
	returns cross product of input vectors
*/
t_vec	cross(t_vec a, t_vec b)
{
	t_vec	t;

	t.x = a.y * b.z - a.z * b.y;
	t.y = a.z * b.x - a.x * b.z;
	t.z = a.x * b.y - a.y * b.x;
	return (t);
}
