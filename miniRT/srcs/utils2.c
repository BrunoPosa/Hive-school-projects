/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/23 12:32:08 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
	Cdataed by mlx_resize_hook, adjusts mlx img and variables with new dimensions.
	Closes window on error.
*/
void	resizer(int32_t width, int32_t height, void* param)
{
	t_rt		*data;

	data = param;
	if (!param || width <= 0 || height <= 0)
		return ;
	data->mlx->width = width;
	data->mlx->height = height;
	data->scene.window.w = width;
	data->scene.window.h = height;
	data->scene.aspect_r = (float)width / (float)height;
	if (!mlx_resize_image(data->img, width, height))
	{
		printf("resizing error!\n");
		mlx_close_window(data->mlx);//?
		return ;
	}
	render_image(&data->scene, data->img);
}

/*
	Returns bottom left corner ray of viewplane. Calculates and saves viewplane
	step/offset	vectors for x and y into scene->cam.x_step and scene->cam.y_step.
	Viewplane is standardized to be 2.0f units on y axis (and starts as 2.0 on x)
*/
t_vec viewplane_offsets(t_scene *scene, t_vec eye)
{
	t_vec	forward;
	t_vec	up;
	t_vec	right;
	t_vec	center;
	t_vec	half_viewplane_width;
	t_vec	corner;

	forward = scene->cam.axis;
	up = create_vec(0, 1, 0);
	if (fabs(dot(forward, up)) > 0.99)
		up = create_vec(0, 0, 1);
	right = normalize(cross(up, forward));
	up = normalize(cross(forward, right));
	center = add(eye, scale(forward, scene->cam.foc_len));
	half_viewplane_width = scale(right, scene->aspect_r);
	corner = subtract(subtract(center, half_viewplane_width), up);
	scene->cam.x_step = scale(scale(right, 2.0f / scene->window.w),
		scene->aspect_r);
	scene->cam.y_step = scale(up, 2.0f / scene->window.h);
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

t_colour	black(void)
{
	return (create_colour(0, 0, 0));
}
