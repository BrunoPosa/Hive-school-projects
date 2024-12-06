/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:04:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 11:23:45 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

float	dist_disk(const t_ray *ray, t_object *obj)
{
	float	p_dist;
	t_vec3	hit_point;
	t_vec3	co;
	float	dist2;

	p_dist = dist_plane(ray, obj);
	if (p_dist == FLT_MAX || p_dist < EPSILON)
		return (FLT_MAX);
	hit_point = vec3_add(ray->origin,
			vec3_multf(ray->direction, p_dist));
	co = vec3_sub(hit_point, obj->disk.pos);
	dist2 = vec3_dot(co, co);
	if (dist2 > EPSILON * EPSILON && dist2 <= obj->disk.radius * \
		obj->disk.radius)
		return (p_dist);
	return (FLT_MAX);
}
