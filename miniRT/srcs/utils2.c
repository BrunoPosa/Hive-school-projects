/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/15 15:34:00 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

t_vec calculate_viewplane(t_scene *scene, t_vec eye)
{
	t_vec	forward;
	t_vec	up;
	t_vec	right;
	t_vec	center;
	t_vec	halfwin_x;
	t_vec	halfwin_y;
	t_vec	corner;

	forward = scene->cam.axis;
	up = create_vec(0, 1, 0);
	if (fabs(dot(forward, up)) > 0.99)
		up = create_vec(0, 0, 1);
	right = normalize(cross(up, forward));
	up = normalize(cross(forward, right));
	center = add(eye, multiply_tuple(forward, scene->cam.foc_len));
	halfwin_x = multiply_tuple(right, scene->half_new_winsize);
	halfwin_y = multiply_tuple(up, scene->half_new_winsize);
	corner = subtract(subtract(center, halfwin_x), halfwin_y);
	scene->cam.x_step = multiply_tuple(right, scene->world_scale);
	scene->cam.y_step = multiply_tuple(up, scene->world_scale);
	return (corner);
}
