/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:48:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:50:26 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	create_vec(float x, float y, float z)
{
	t_vec	t;

	t.x = x;
	t.y = y;
	t.z = z;
	return (t);
}

t_rgb	create_colour(float r, float g, float b)
{
	t_rgb	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}
