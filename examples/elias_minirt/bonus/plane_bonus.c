/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:14:05 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

t_inters	*plane_intersect(t_object *plane, float **ray)
{
	t_inters	*cross;
	float		t;

	(void)plane;
	cross = create_intersections(3);
	if (!cross)
		return (NULL);
	if (fabs(ray[1][1]) < EPS)
		return (cross);
	t = (ray[0][1] * -1 / ray[1][1]);
	cross->count++;
	cross->t[0] = t;
	cross->objects[cross->count - 1] = plane;
	cross->objects[cross->count] = NULL;
	return (cross);
}
