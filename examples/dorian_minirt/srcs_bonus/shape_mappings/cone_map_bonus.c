/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:04:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:05:27 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include "objects_bonus.h"

#ifndef EPSILON
# define EPSILON 10e-6
#endif

t_vec2	cone_map(t_vec3 *point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	offset;
	t_vec3	projection;
	t_vec3	axis[2];
	float	angle;

	if (obj->cone.disk_hit)
		return (disk_map(point, obj->cone.bottom));
	offset = vec3_sub(*point, obj->cone.pos);
	axis[U] = vec3_cross((t_vec3){EPSILON, 1, EPSILON}, obj->cone.normal);
	vec3_normalize(&(axis[U]));
	axis[V] = vec3_cross(obj->cone.normal, axis[U]);
	vec3_normalize(&(axis[V]));
	projection.x = vec3_dot(offset, axis[U]);
	projection.y = vec3_dot(offset, axis[V]);
	projection.z = vec3_dot(offset, obj->cone.normal);
	angle = atan2(projection.y, projection.x);
	if (angle < 0.0)
		angle += 2.0f * M_PI;
	uv.x = angle * M_1_DIV_2PI;
	uv.y = projection.z / obj->cone.height;
	return (uv);
}
