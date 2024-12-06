/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:40:55 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "shaders_bonus.h"

float	dist_plane(const t_ray *ray, t_object *obj)
{
	float	denominator;
	float	distance;

	denominator = vec3_dot(obj->plane.normal, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (FLT_MAX);
	distance = vec3_dot(vec3_sub(obj->plane.pos, ray->origin),
			obj->plane.normal) / denominator;
	if (distance < EPSILON)
		return (FLT_MAX);
	return (distance);
}
