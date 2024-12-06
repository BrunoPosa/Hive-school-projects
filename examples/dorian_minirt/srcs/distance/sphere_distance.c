/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:49:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 13:07:03 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

float	dist_sphere(const t_ray *ray, t_object *obj)
{
	t_vec3	c_dist;
	t_vec3	parameter;
	float	discriminant;
	t_vec2	res;
	float	inv_divisor;

	c_dist = vec3_sub(ray->origin, obj->sphere.pos);
	parameter.x = vec3_dot(ray->direction, ray->direction);
	parameter.y = 2.0 * vec3_dot(c_dist, ray->direction);
	parameter.z = vec3_dot(c_dist, c_dist) - obj->sphere.radius2;
	discriminant = parameter.y * parameter.y - 4 * parameter.x * parameter.z;
	if (discriminant < EPSILON)
		return (FLT_MAX);
	inv_divisor = 1 / (2.0 * parameter.x);
	res.x = (-parameter.y - sqrt(discriminant)) * inv_divisor;
	res.y = (-parameter.y + sqrt(discriminant)) * inv_divisor;
	if (res.x > EPSILON)
		return (res.x);
	if (res.y > EPSILON)
		return (res.y);
	return (FLT_MAX);
}
