/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:11:40 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/28 12:54:43 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "minirt.h"

float	which_pos_min(float a, float b, float c)
{
	float	min;

	min = FLT_MAX;
	if (isnan(a) == 0 && a > EPSILON)
		min = a;
	if (isnan(b) == 0 && b > EPSILON && b < min)
		min = b;
	if (isnan(c) == 0 && c > EPSILON && c < min)
		min = c;
	return (min);
}

static void	dist_caps(const t_ray *ray, const t_object *obj,
	float dist_cap[2])
{
	float	dist;

	dist_cap[0] = dist_disk(ray, obj->cylinder.bottom);
	dist = fminf(dist_disk(ray, obj->cylinder.top), dist_cap[0]);
	dist_cap[1] = 0;
	if (dist_cap[0] != FLT_MAX && dist_cap[0] > EPSILON)
		dist_cap[1] = 1;
	if (dist > EPSILON && dist < dist_cap[0])
		dist_cap[1] = 2;
	dist_cap[0] = fmin(dist_cap[0], dist);
}

static void	check_height(const t_ray *ray, const t_cylinder *cylinder,
			float *dist)
{
	t_vec3	hitpoint;
	t_vec3	top_cap;
	t_vec3	bottom_cap;

	top_cap = vec3_add(cylinder->pos, vec3_multf(cylinder->normal,
				cylinder->height / 2));
	bottom_cap = vec3_sub(cylinder->pos, vec3_multf(cylinder->normal,
				cylinder->height / 2));
	hitpoint = vec3_add(ray->origin, vec3_multf(ray->direction, *dist));
	if (vec3_dot(cylinder->normal, vec3_sub(hitpoint, bottom_cap)) <= EPSILON)
		*dist = FLT_MAX;
	if (vec3_dot(cylinder->normal, vec3_sub(hitpoint, top_cap)) >= EPSILON)
		*dist = FLT_MAX;
}

static void	calc_temps(const t_ray *ray, const t_cylinder *cylinder,
		t_vec3 *temp)
{
	temp[ORTHO] = vec3_sub(ray->direction, vec3_multf(cylinder->normal,
				vec3_dot(ray->direction, cylinder->normal)));
	temp[AXIS] = vec3_sub(vec3_sub(ray->origin, cylinder->pos),
			vec3_multf(cylinder->normal,
				vec3_dot(vec3_sub(ray->origin, cylinder->pos),
					cylinder->normal)));
}

float	dist_cylinder(const t_ray *ray, t_object *obj)
{
	t_vec3	temp[2];
	t_vec3	params;
	float	discriminant;
	float	res[2];
	float	dist_cap[2];

	calc_temps(ray, &(obj->cylinder), temp);
	params.x = vec3_dot(temp[0], temp[0]);
	params.y = 2 * vec3_dot(temp[0], temp[1]);
	params.z = vec3_dot(temp[1], temp[1]) - (obj->cylinder.radius2);
	discriminant = params.y * params.y - 4 * params.x * params.z;
	if (discriminant < EPSILON)
		return (FLT_MAX);
	res[0] = (-params.y - sqrt(discriminant)) / (2 * params.x);
	res[1] = (-params.y + sqrt(discriminant)) / (2 * params.x);
	if (isnan(res[0]) == 0 && res[0] > EPSILON)
		check_height(ray, &(obj->cylinder), &(res[0]));
	if (isnan(res[1]) == 0 && res[1] > EPSILON)
		check_height(ray, &(obj->cylinder), &(res[1]));
	dist_caps(ray, obj, dist_cap);
	res[0] = which_pos_min(res[0], res[1], dist_cap[0]);
	if (isnan(res[0]) == 0 && res[0] == dist_cap[0] && res[0] != FLT_MAX)
		obj->cylinder.disk_hit = dist_cap[0];
	return (res[0]);
}
