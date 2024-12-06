/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/28 12:54:47 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders_bonus.h"

float	dist_mesh(const t_ray *ray, t_object *obj)
{
	int		j;
	float	new_dist;
	float	hit_dist;

	j = 0;
	new_dist = 0;
	hit_dist = FLT_MAX;
	while (j < obj->mesh.n_triangles)
	{
		new_dist = dist_triangle(ray, &obj->mesh.triangle_data[j]);
		if (new_dist < hit_dist)
		{
			obj->mesh.obj_id = j;
			hit_dist = new_dist;
		}
		j++;
	}
	return (hit_dist);
}

float	get_dist(const t_ray *ray, t_object *obj)
{
	static const t_dist_function	func[] = {
		dist_sphere,
		dist_plane,
		dist_cylinder,
		dist_disk,
		dist_triangle,
		dist_cone,
		dist_mesh
	};

	return (func[obj->type](ray, obj));
}

void	get_closest(const t_scene *scene, const t_ray *ray, t_hitresult *hit)
{
	int			i;
	float		new_dist;

	i = 0;
	new_dist = 0;
	hit->distance = FLT_MAX;
	while (scene->objs && i < scene->n_objs)
	{
		new_dist = get_dist(ray, &(scene->objs[i]));
		if (new_dist < hit->distance)
		{
			hit->obj_id = i;
			hit->distance = new_dist;
		}
		i++;
	}
}
