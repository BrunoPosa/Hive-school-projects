/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_colours.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:42:35 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/15 15:43:58 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

t_colour	add_colours(t_colour a, t_colour b)
{
	t_colour	c;

	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return (c);
}

t_colour	subtract_colours(t_colour a, t_colour b)
{
	t_colour	c;

	c.r = a.r - b.r;
	c.g = a.g - b.g;
	c.b = a.b - b.b;
	return (c);
}

t_colour	scale_colour(t_colour a, float scaler)
{
	t_colour	c;

	c.r = a.r * scaler;
	c.g = a.g * scaler;
	c.b = a.b * scaler;
	return (c);
}

t_colour	hadamard_product(t_colour a, t_colour b)
{
	t_colour	c;

	c.r = clamp((a.r * b.r) / 255.0);
	c.g = clamp((a.g * b.g) / 255.0);
	c.b = clamp((a.b * b.b) / 255.0);
	return (c);
}
