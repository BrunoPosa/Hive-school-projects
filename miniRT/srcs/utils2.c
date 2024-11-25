/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/11/24 17:19:18 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// t_tuple *calculate_camera_ray(t_scene *scene, t_tuple *camera, float x, float y)
// {
// 	t_tuple	*ray;
// 	t_tuple	*ray_viewplane;

// 	ray = NULL;
// 	ray_viewplane = create_point(x, y, camera->z + scene->camera.focal_length);
// 	if (!ray_viewplane)
// 		return (free(camera), ray);
// 	ray = subtract(ray_viewplane, camera);
// 	if (!ray)
// 		return (free(ray_viewplane), ray);
// 	ray = normalize(ray);
// 	if (!ray)
// 		free(ray_viewplane);
// 	return (ray);
// }
t_tuple *calculate_camera_ray(t_scene *scene, t_tuple *camera, int i, int j)
{
    t_tuple *ray;
    t_tuple *ray_viewplane;
    float x;
    float y;

    x = scene->world_scale * i - scene->half_new_winsize;
    y = scene->world_scale * j - scene->half_new_winsize;
	ray = NULL;
	ray_viewplane = create_point(x, y, camera->z + scene->camera.focal_length);
	if (!ray_viewplane)
		return (free(camera), ray);
	ray = subtract(ray_viewplane, camera);
	if (!ray)
		return (free(ray_viewplane), ray);
	ray = normalize(ray);
	if (!ray)
		free(ray_viewplane);
	return (ray);
}

void	precalculate(t_scene *scene)
{
	scene->world_scale = (float)WRLD_WINWIDTH / WINSIZE;
	scene->half_new_winsize = (float)WRLD_WINWIDTH / 2;
}
