/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tuples2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:52:19 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
	returns number of differences between the two vectors/points, 0 if identical
*/
int	diff(t_vec a, t_vec b)
{
	int	diff_count;

	diff_count = 0;
	if (fabs(a.x - b.x) > EPSILON)
		diff_count++;
	if (fabs(a.y - b.y) > EPSILON)
		diff_count++;
	if (fabs(a.z - b.z) > EPSILON)
		diff_count++;
	return (diff_count);
}

t_vec	add(t_vec a, t_vec b)
{
	t_vec	t;

	t.x = a.x + b.x;
	t.y = a.y + b.y;
	t.z = a.z + b.z;
	return (t);
}

t_vec	subtract(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

/*
	returns an inverted tuple
*/
t_vec	negate(t_vec t)
{
	t_vec	res;

	res.x = -t.x;
	res.y = -t.y;
	res.z = -t.z;
	return (res);
}

/*
	returns a tuple with each member multiplied
*/
t_vec	scale(t_vec t, float scaler)
{
	t_vec	res;

	res.x = t.x * scaler;
	res.y = t.y * scaler;
	res.z = t.z * scaler;
	return (res);
}
