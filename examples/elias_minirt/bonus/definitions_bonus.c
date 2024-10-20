/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:20:16 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

t_light	*create_light(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->coord = create_point(0, 0, 0);
	light->color = color(1, 1, 1);
	light->brightness = 0.5;
	return (light);
}

float	*tuple(float a, float b, float c, float w)
{
	float	*p;

	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	p[0] = a;
	p[1] = b;
	p[2] = c;
	p[3] = w;
	return (p);
}

float	*create_point(float a, float b, float c)
{
	return (tuple(a, b, c, 1));
}

float	*create_vector(float a, float b, float c)
{
	return (tuple(a, b, c, 0));
}

t_light	*point_light(float *p, float *c)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->coord = p;
	light->color = c;
	return (light);
}
