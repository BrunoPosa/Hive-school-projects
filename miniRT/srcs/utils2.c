/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/18 15:50:53 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
	Returns bottom left corner ray of viewplane. Calculates and saves viewplane
	step/offset	vectors for x and y into scene->cam.x_step and scene->cam.y_step.
*/
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
	center = add(eye, scale(forward, scene->cam.foc_len));//maybe focal len needs to change if window size changes?
	halfwin_x = scale(right, scene->viewplane.w / 2);//do we need to round?
	halfwin_y = scale(up, scene->viewplane.h / 2);
	corner = subtract(subtract(center, halfwin_x), halfwin_y);
	scene->cam.x_step = scale(right, scene->aspect_r * (scene->viewplane.w / scene->window.w));
	scene->cam.y_step = scale(up, (scene->viewplane.h / scene->window.h));
	return (corner);
}

/*
	Returns 0 if hitpoint at t is out of vertical cylinder bounds, or if
	t <= EPSILON. Returns unmodified t if within bounds.
*/
float	cyl_height_check(t_vec ray, t_vec origin, float t, t_shape *cyl)
{
	t_vec	hitpoint;
	float	projection;

	ft_memset(&hitpoint, 0, sizeof(t_vec));
	if (t <= EPSILON || !cyl)
		return (0.0f);
	hitpoint = add(origin, scale(ray, t));
	projection = dot(subtract(hitpoint, cyl->xyz), cyl->axis);
	if (projection < 0 || projection > cyl->h)
		return (0.0f);
	return (t);
}

/*
	Returns 0 if hitpoint at t is out of bounds of given cylinder top/base disc
	radius, or if t <= EPSILON. Returns unmodified t if within bounds.
*/
float	cyl_radius_check(t_vec ray, t_vec origin, float t, t_shape *cap)
{
	t_vec	hitpoint;

	ft_memset(&hitpoint, 0, sizeof(t_vec));
	if (t <= EPSILON || !cap)
		return (0.0f);
	hitpoint = add(origin, scale(ray, t));
	if (magnitude(subtract(hitpoint, cap->xyz)) > cap->r)
		return (0.0f);
	return (t);
}
