/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planar_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:48:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/28 12:54:54 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_bonus.h"

#ifndef EPSILON
# define EPSILON 10e-6
#endif

t_vec2	plane_map(t_vec3 *point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	axis[2];

	axis[U] = vec3_cross(obj->plane.normal, (t_vec3){(float)INT_MAX,
			(float)INT_MAX, (float)INT_MAX});
	vec3_normalize(&axis[U]);
	axis[V] = vec3_cross(axis[U], obj->plane.normal);
	uv.x = ft_frac(vec3_dot(*point, axis[U]));
	uv.y = ft_frac(vec3_dot(*point, axis[V]));
	return (uv);
}

t_vec2	disk_map(t_vec3 *point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	point_t;
	float	angle;
	t_vec3	axis[2];

	point_t = vec3_sub(*point, obj->disk.pos);
	axis[U] = vec3_cross((t_vec3){EPSILON, 1, EPSILON},
			obj->disk.normal);
	vec3_normalize(&axis[U]);
	axis[V] = vec3_cross(obj->disk.normal, axis[U]);
	uv.x = vec3_dot(point_t, axis[U]);
	uv.y = vec3_dot(point_t, axis[V]);
	angle = atan2(uv.y, uv.x);
	if (angle < 0.0)
		angle += 2.0 * M_PI;
	uv.x = angle * M_1_DIV_2PI;
	uv.y = ft_frac(vec3_mag(point_t) / obj->disk.radius);
	return (uv);
}
