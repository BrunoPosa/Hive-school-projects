/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:31:35 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 14:09:55 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/vector.h"

float	ft_sqr(float n)
{
	return (n * n);
}

float	vec_len(t_vec v)
{
	float	l;

	l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (l);
}

t_vec	vec_add(t_vec v, t_vec u)
{
	t_vec	w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

t_vec	vec_sub(t_vec v, t_vec u)
{
	t_vec	w;

	w.x = v.x - u.x;
	w.y = v.y - u.y;
	w.z = v.z - u.z;
	return (w);
}

t_vec	vec_neg(t_vec v)
{
	t_vec	w;

	w.x = -v.x;
	w.y = -v.y;
	w.z = -v.z;
	return (w);
}
