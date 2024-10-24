/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:31:16 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 14:10:13 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/vector.h"

t_vec	vec_mult(t_vec v, float a)
{
	t_vec	w;

	w.x = a * v.x;
	w.y = a * v.y;
	w.z = a * v.z;
	return (w);
}

t_vec	vec_div(t_vec v, float a)
{
	t_vec	w;

	if (a == 0)
	{
		printf("Can't divide with zero!\n");
		exit(1);
	}
	w.x = v.x / a;
	w.y = v.y / a;
	w.z = v.z / a;
	return (w);
}

float	dot_prod(t_vec v, t_vec u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

t_vec	cross_prod(t_vec v, t_vec u)
{
	t_vec	w;

	w.x = v.y * u.z - v.z * u.y;
	w.y = v.z * u.x - v.x * u.z;
	w.z = v.x * u.y - v.y * u.x;
	return (w);
}

t_vec	vec_norm(t_vec v)
{
	t_vec	w;

	w = vec_div(v, vec_len(v));
	return (w);
}
