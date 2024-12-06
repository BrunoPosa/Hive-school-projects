/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/06 21:24:25 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

t_tuple *calculate_camera_ray(t_scene *scene, t_tuple *camera, int i, int j)
{
	t_tuple *ray;
	t_tuple	*cam_forward;
	t_tuple	*cam_right;
	t_tuple	*cam_up;
	t_tuple	*viewcenter;
	t_tuple	*viewcorner;
	t_tuple	*pixel_step_x;
	t_tuple	*pixel_step_y;
	t_tuple	*pixel;

	cam_forward = normalize(&scene->camera.xyz3d);
	cam_right = normalize(cross(cam_forward, create_vector(0, 1, 0)));
	cam_up = normalize(cross(cam_right, cam_forward));
	viewcenter = add(camera, multiply_tuple(cam_forward, scene->camera.focal_length));
	viewcorner = subtract(subtract(viewcenter, multiply_tuple(cam_right, scene->half_new_winsize)), multiply_tuple(cam_up, scene->half_new_winsize));
	pixel_step_x = multiply_tuple(cam_right, scene->world_scale);
	pixel_step_y = multiply_tuple(cam_up, scene->world_scale);
	pixel = add(viewcorner, add(multiply_tuple(pixel_step_x, i), multiply_tuple(pixel_step_y, j)));
	ray = normalize(subtract(pixel, camera));
	ray->w = VECTOR;
	return (ray);
}

void	precalculate(t_scene *scene)
{
	scene->world_scale = (float)WRLD_WINSIZE / WINSIZE;
	scene->half_new_winsize = (float)WRLD_WINSIZE / 2;
}

int	init_trace_data(t_scene *scene)
{
	scene->data = ft_calloc(1, sizeof(t_data));
	if (!scene->data)
		return (ERROR);
	scene->data->hitmin = (float)INT32_MAX;
	return (SUCCESS);
}