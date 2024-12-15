/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:38 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

t_vec viewplane_offsets(t_scene *scene, t_vec eye)
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
	center = add(eye, scale(forward, scene->cam.foc_len));
	halfwin_x = scale(right, scene->half_new_winsize);
	halfwin_y = scale(up, scene->half_new_winsize);
	corner = subtract(subtract(center, halfwin_x), halfwin_y);
	scene->cam.x_step = scale(right, scene->world_scale);
	scene->cam.y_step = scale(up, scene->world_scale);
	return (corner);
}
