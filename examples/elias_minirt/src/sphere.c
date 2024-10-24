/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:50:17 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/23 12:30:36 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static float	*get_values(t_object *sp, float **r)
{
	float	*vals;
	float	*sp_to_ray;
	float	*spcoord;

	(void)sp;
	spcoord = create_point(0, 0, 0);
	sp_to_ray = tuple_subs(r[ORIGIN], spcoord);
	free(spcoord);
	if (!sp_to_ray)
		return (NULL);
	vals = tuple(1, 1, 1, 1);
	if (!vals)
	{
		free(sp_to_ray);
		return (NULL);
	}
	vals[0] = dot_product(r[DIRECTION], r[DIRECTION]);
	vals[1] = 2 * dot_product(r[DIRECTION], sp_to_ray);
	vals[2] = dot_product(sp_to_ray, sp_to_ray) - 1;
	free(sp_to_ray);
	return (vals);
}

t_inters	*sphere_intersect(t_object *sp, float **r)
{
	t_inters	*cross;
	float		*vals;
	float		discrim;

	vals = get_values(sp, r);
	if (!vals)
		return (NULL);
	discrim = vals[1] * vals[1] - (4 * vals[0] * vals[2]);
	if (discrim < 0)
	{
		free(vals);
		return (NULL);
	}
	cross = create_intersections(3);
	if (!cross)
		return (NULL);
	cross->t[0] = (-vals[1] - sqrt(discrim)) / (2 * vals[0]);
	cross->t[1] = (-vals[1] + sqrt(discrim)) / (2 * vals[0]);
	cross->objects[0] = sp;
	cross->objects[1] = sp;
	cross->count = 2;
	cross->objects[2] = NULL;
	free(vals);
	return (cross);
}
