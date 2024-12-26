/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tuples2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:52:19 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 04:00:31 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
