/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/11 18:23:50 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

t_vec calculate_camera_ray(t_scene *scene, t_vec camera, int i, int j)
{
	t_vec	ray;
	t_vec	cam_forward;
	t_vec	cam_right;
	t_vec	cam_up;
	t_vec	viewcenter;
	t_vec	viewcorner;
	t_vec	pixel_step_x;
	t_vec	pixel_step_y;
	t_vec	pixel;
	t_vec	up;

	cam_forward = scene->camera.xyz3d;
	up = create_vec(0, 1, 0);
	if (fabs(dot(cam_forward, up)) > 0.99)
		up = create_vec(0, 0, 1);
	cam_right = normalize(cross(up, cam_forward));
	cam_up = normalize(cross(cam_forward, cam_right));
	viewcenter = add(camera, multiply_tuple(cam_forward, scene->camera.focal_length));
	viewcorner = subtract(subtract(viewcenter, multiply_tuple(cam_right, scene->half_new_winsize)), multiply_tuple(cam_up, scene->half_new_winsize));
	pixel_step_x = multiply_tuple(cam_right, scene->world_scale);
	pixel_step_y = multiply_tuple(cam_up, scene->world_scale);
	pixel = add(viewcorner, add(multiply_tuple(pixel_step_x, i), multiply_tuple(pixel_step_y, j)));
	ray = normalize(subtract(pixel, camera));
	return (ray);
}
