/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:28:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 18:26:29 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "minirt.h"

int32_t	vec4_toint32(t_vec4 colour)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	t;

	t = 1;
	r = 255 * colour.x;
	g = 255 * colour.y;
	b = 255 * colour.z;
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

t_vec4	ft_int32tov4(int32_t colour)
{
	t_vec4	result;

	result.v = get_t(colour);
	result.x = get_r(colour);
	result.y = get_g(colour);
	result.z = get_b(colour);
	return (result);
}

t_vec4	ft_trgbtov4(int colour[4])
{
	t_vec4	result;

	result.v = 1;
	result.x = (float) colour[1];
	result.y = (float) colour[2];
	result.z = (float) colour[3];
	return (result);
}

void	ft_rgbtonorm(t_vec4 *colour)
{
	colour->v = 1;
	colour->x /= 255.0;
	colour->y /= 255.0;
	colour->z /= 255.0;
}
