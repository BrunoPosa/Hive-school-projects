/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:35:03 by bposa             #+#    #+#             */
/*   Updated: 2024/12/20 15:09:29 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
	Called by mlx_resize_hook, adjusts mlx img and variables with new dimensions.
*/
void	resizer(int32_t width, int32_t height, void* param)
{
	t_rt		*all;
	mlx_image_t	*tmp;

	tmp = NULL;
	all = param;
	if (!param)
		return ;
	tmp = all->img;
	all->mlx->width = width;//maybe not needed?
	all->mlx->height = height;//maybe not needed?
	all->scene.window.w = width;
	all->scene.window.h = height;
	all->scene.aspect_r = (float)width / (float)height;
	all->scene.hscale = 2.0f / (float)width;
	all->scene.vscale = 2.0f / (float)height;
	if (!mlx_resize_image(all->img, width, height))
	{
		printf("resizing error!\n");
		mlx_close_window(all->mlx);//?
		return ;
	}
	render_image(&all->scene, all->img);
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
	scene->cam.x_step = scale(scale(right, scene->hscale), scene->aspect_r);
	scene->cam.y_step = scale(up, scene->vscale);
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
