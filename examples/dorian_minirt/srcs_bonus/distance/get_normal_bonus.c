/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:05:10 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders_bonus.h"

static t_vec3	pertub_disk_normal(const t_disk *disk, const t_vec3 *hit)
{
	static const t_vec3	perturbation = (t_vec3){0.1, 0.1, 0.1};
	float				edge_dist;
	t_vec3				normal;

	edge_dist = vec3_dist(*hit, disk->pos);
	edge_dist /= disk->radius;
	normal = vec3_propadd(disk->normal, perturbation, edge_dist);
	return (normal);
}

static t_vec3	get_cylinder_normal(t_cylinder *cylinder,
	const t_vec3 *hitpoint)
{
	t_vec3				co;
	t_vec3				normal;

	if (cylinder->disk_hit == 1)
		normal = pertub_disk_normal(&cylinder->bottom->disk, hitpoint);
	if (cylinder->disk_hit == 2)
		normal = pertub_disk_normal(&cylinder->bottom->disk, hitpoint);
	else
	{
		co = vec3_sub(*hitpoint, cylinder->pos);
		normal = vec3_sub(co, vec3_multf(cylinder->normal,
					vec3_dot(cylinder->normal, co)));
	}
	cylinder->disk_hit = 0;
	return (normal);
}

t_vec3	get_cone_normal( t_cone *cone, const t_vec3 hitpoint)
{
	t_vec3			co;
	t_vec3			normal;
	static t_vec3	prev_normal;

	if (cone->disk_hit)
		normal = cone->bottom->disk.normal;
	else
	{
		co = vec3_sub(hitpoint, cone->pos);
		normal = vec3_cross(co, vec3_cross(co, cone->normal));
		if ((fabsf(normal.x - prev_normal.x) < 0.01
				&& fabsf(normal.y - prev_normal.y) < 0.01
				&& fabsf(normal.z - prev_normal.z) < 0.01))
		prev_normal = normal;
	}
	cone->disk_hit = 0;
	return (normal);
}

t_vec3	get_normal(t_object *obj, t_vec3 hitpoint)
{
	t_vec3	normal;

	if (obj->type == sphere_obj)
		normal = vec3_sub(hitpoint, obj->sphere.pos);
	else if (obj->type == mesh_obj)
		normal = obj->mesh.triangle_data[obj->mesh.obj_id].triangle.normal;
	else if (obj->type == plane_obj)
		return (obj->plane.normal);
	else if (obj->type == disk_obj)
		return (obj->disk.normal);
	else if (obj->type == triangle_obj)
		normal = vec3_cross(obj->triangle.edges[1], obj->triangle.edges[0]);
	else if (obj->type == cylinder_obj)
		normal = get_cylinder_normal(&(obj->cylinder), &hitpoint);
	else if (obj->type == cone_obj)
		normal = get_cone_normal(&(obj->cone), hitpoint);
	vec3_normalize(&normal);
	return (normal);
}
