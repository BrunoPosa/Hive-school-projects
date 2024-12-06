/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_visibility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:36:39 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/28 11:10:12 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "shaders.h"

int	is_light_visible(const t_vec3 cam_pos, const t_vec3 light_pos,
	const t_vec3 pos, t_vec3 *normal)
{
	float	side1;
	float	side2;
	t_vec3	normal_light;

	side1 = vec3_dot(vec3_sub(cam_pos, pos), *normal);
	normal_light = vec3_sub(light_pos, pos);
	side2 = vec3_dot(normal_light, *normal);
	if ((side1 < 0 && side2 < 0) || (side1 >= 0 && side2 >= 0))
	{
		if (side1 < 0 && side2 < 0)
			*normal = vec3_neg(*normal);
		return (1);
	}
	if (side1 < 0)
	{
		*normal = vec3_neg(*normal);
		return (0);
	}
	return (0);
}

static void	cap_visibility(t_cylinder *cylinder, t_camera *cam, t_light *light)
{
	cylinder->bottom->disk.isvisible = is_light_visible(
			cam->pos,
			light->pos,
			cylinder->bottom->disk.pos,
			&(cylinder->bottom->disk.normal));
	cylinder->top->disk.isvisible = cylinder->bottom->disk.isvisible;
}

void	check_visibility(t_scene *scene, int id)
{
	if (scene->objs[id].type == plane_obj)
	{
		scene->objs[id].plane.isvisible = is_light_visible(scene->cam.pos,
				scene->objs[id].plane.pos, scene->objs[id].plane.pos,
				&scene->objs[id].plane.normal);
	}
	if (scene->objs[id].type == disk_obj)
		scene->objs[id].disk.isvisible = is_light_visible(scene->cam.pos,
				scene->objs[id].plane.pos, scene->objs[id].disk.pos,
				&scene->objs[id].disk.normal);
	if (scene->objs[id].type == cylinder_obj)
		cap_visibility(&scene->objs[id].cylinder, &scene->cam, scene->lights);
}
