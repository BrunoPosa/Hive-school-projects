/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 07:32:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 17:18:10 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "objects.h"
#include "shaders.h"
#include "minirt.h"

t_vec4	get_hitcolour(const t_object *obj)
{
	if (obj->type == sphere_obj)
		return (obj->sphere.colour);
	else if (obj->type == plane_obj)
		return (obj->plane.colour);
	else if (obj->type == cylinder_obj)
		return (obj->cylinder.colour);
	else if (obj->type == disk_obj)
		return (obj->disk.colour);
	else if (obj->type == triangle_obj)
		return (obj->triangle.colour);
	else if (obj->type == cone_obj)
		return (obj->cone.colour);
	else
		return ((t_vec4){1, 0, 0, 0});
}

void	set_hitpoint(t_scene *scene, t_ray *ray, t_hitresult *hit)
{
	hit->position = vec3_add(ray->origin,
			vec3_multf(ray->direction, hit->distance));
	hit->point2cam = vec3_sub(hit->position, ray->origin);
	vec3_normalize(&hit->point2cam);
	hit->colour = get_hitcolour(&(scene->objs[hit->obj_id]));
	hit->normal = get_normal(&(scene->objs[hit->obj_id]), hit->position);
	hit->position = vec3_add(hit->position, vec3_multf(hit->normal, 10e-3));
}
