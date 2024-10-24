/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:49:14 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 14:16:14 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static int	is_shadowed_help(t_inters *xs, float d)
{
	t_inter	*i;

	i = hit(xs);
	clean_intersections(xs);
	if (!i)
		return (0);
	if (i->t != -1 && i->t < d)
	{
		free(i);
		return (1);
	}
	free(i);
	return (0);
}

int	is_shadowed(t_world *w, float *p, t_light *l)
{
	float		*v;
	float		*direction;
	float		**ray;
	float		distance;
	t_inters	*xs;

	v = tuple_subs(l->coord, p);
	distance = magnitude(v);
	direction = normalize(v, 1);
	ray = create_ray(p, direction);
	xs = intersect_world(w, ray);
	free(direction);
	free(ray);
	if (!xs)
		return (0);
	return (is_shadowed_help(xs, distance));
}
