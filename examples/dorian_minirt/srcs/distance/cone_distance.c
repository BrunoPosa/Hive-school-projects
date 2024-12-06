/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:28:17 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/25 13:07:29 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

static void	check_height(const t_ray *ray, const t_cone *cone,
			float *dist)
{
	t_vec3	hitpoint;

	hitpoint = vec3_add(ray->origin, vec3_multf(ray->direction, *dist));
	if (vec3_dot(cone->normal,
			vec3_sub(hitpoint, cone->bottom->disk.pos)) >= EPSILON
		|| vec3_dot(cone->normal, vec3_sub(hitpoint, cone->pos)) <= EPSILON)
		*dist = FLT_MAX;
}

static t_vec3	get_params(const t_ray *ray, const t_object	*obj)
{
	t_vec3	oc;
	t_vec3	params;
	float	angle;
	float	dot_prods[2];

	oc = vec3_sub(ray->origin, obj->cone.pos);
	angle = (1 + obj->cone.radius2 / (obj->cone.height2));
	dot_prods[0] = vec3_dot(ray->direction, obj->cone.normal);
	dot_prods[1] = vec3_dot(oc, obj->cone.normal);
	params.x = vec3_dot(ray->direction, ray->direction) - \
		angle * pow(dot_prods[0], 2);
	params.y = 2 * (vec3_dot(ray->direction, oc) - \
		angle * dot_prods[0] * dot_prods[1]);
	params.z = vec3_dot(oc, oc) - angle * pow(dot_prods[1], 2);
	return (params);
}

float	dist_cone(const t_ray *ray, t_object *obj)
{
	t_vec3	params;
	float	discriminant;
	float	res[2];
	float	dist_cap;

	params = get_params(ray, obj);
	discriminant = params.y * params.y - 4 * params.x * params.z;
	if (discriminant < EPSILON)
		return (FLT_MAX);
	res[0] = (-params.y - sqrt(discriminant)) / (2 * params.x);
	res[1] = (-params.y + sqrt(discriminant)) / (2 * params.x);
	if (res[0] > EPSILON)
		check_height(ray, &(obj->cone), &(res[0]));
	if (res[1] > EPSILON)
		check_height(ray, &(obj->cone), &(res[1]));
	dist_cap = dist_disk(ray, obj->cone.bottom);
	res[0] = which_pos_min(res[0], res[1], dist_cap);
	if (isnan(res[0]) == 0 && res[0] == dist_cap && res[0] != FLT_MAX)
		obj->cone.disk_hit = 1;
	return (res[0]);
}
