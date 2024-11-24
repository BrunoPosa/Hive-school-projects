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

t_tuple *calculate_camera_ray(t_scene *scene, t_tuple *camera, float x, float y)
{
	t_tuple	*ray;
	t_tuple	*ray_viewplane;

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
