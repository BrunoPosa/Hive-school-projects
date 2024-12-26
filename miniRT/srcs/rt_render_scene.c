/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/12/26 03:58:57 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

bool	in_shadow(t_scene *scene, t_raydata *rayd)
{
	int			i;
	float		hit;
	float		distance;
	float		light_distance;

	i = 0;
	hit = 0.0;
	light_distance = magnitude(subtract(scene->lightxyz, rayd->hitp));
	distance = light_distance;
	while (i < scene->shape_count)
	{
		if (rayd->shape != &scene->shapes[i])
		{
			hit = intersectall(rayd->shadow_ray, rayd->hitp, &scene->shapes[i]);
			if (hit > EPSILON && hit < distance)
				distance = hit;
		}
		i++;
	}
	if (distance < light_distance)
		return (1);
	return (0);
}

float	intersectall(t_vec ray, t_vec origin, t_shape *shape)
{
	if (shape->type == sphere)
		return (fsphere(ray, origin, shape));
	else if (shape->type == plane)
		return (fplane(ray, origin, shape));
	else
		return (fcylinder(ray, origin, shape));
}

/*
	returns 1 if ray hits a shape, sets rayd's hitmin (min hit distance)
	and shape pointer to the closest shape. If no shapes intersected, returns 0
*/
bool	closest_shape_hit(t_scene *scene, t_vec ray, t_raydata *rayd)
{
	float	hit;
	int		i;

	hit = 0.0f;
	i = 0;
	rayd->hitmin = INFINITY;
	while (i < scene->shape_count)
	{
		hit = intersectall(ray, scene->cam.eye, &scene->shapes[i]);
		if (hit >= EPSILON && hit < rayd->hitmin)
		{
			rayd->hitmin = hit;
			rayd->shape = &scene->shapes[i];
		}
		i++;
	}
	if (rayd->hitmin < INFINITY)
		return (1);
	return (0);
}

/*
	Sends ray interacting through scene, returns computed uint_32 color for pixel
*/
int	trace(t_scene *scene, t_vec ray)
{
	t_raydata	rayd;

	ft_memset(&rayd, 0, sizeof(t_raydata));
	if (!closest_shape_hit(scene, ray, &rayd))
	{
		rayd.shape = NULL;
		return (to_uint32(scene->ambiant));
	}
	rayd.hitp = add(scene->cam.eye, scale(ray, rayd.hitmin));
	rayd.shadow_ray = subtract(
			add(scene->lightxyz, scale(scene->cam.up, EPSILON)), rayd.hitp);
	rayd.shadow_ray = normalize(rayd.shadow_ray);
	rayd.base_color = hadamard_product(rayd.shape->rgb, scene->ambiant);
	if (in_shadow(scene, &rayd))
	{
		rayd.shape = NULL;
		return (to_uint32(rayd.base_color));
	}
	rayd.normal = surface_normal(scene, rayd.shape, &rayd);
	rayd.diffuse_part = calc_diffuse_part(scene, rayd.shape, &rayd);
	rayd.shape = NULL;
	return (to_uint32(add_colours(rayd.base_color, rayd.diffuse_part)));
}

/*
	img.pixels buffer will display pixels in order from top left to bottom right
	so we invert the y axis to start bottom left like a cartesian coordinate sys.
	we start from the bottom left corner ray, and add to it offset vectors in x
	and y directions, as well as 0.5 to make each ray in the middle of the pixel.
*/
void	render_image(t_scene *scene, mlx_image_t *img)
{
	int		x;
	int		y;
	t_vec	ray;
	t_vec	corner;

	x = -1;
	y = -1;
	ft_memset(&ray, 0, sizeof(t_vec));
	corner = viewplane_offsets(scene, scene->cam.eye);
	while (++x < scene->window.w)
	{
		y = -1;
		while (++y < scene->window.h)
		{
			ray = add(corner, add(scale(scene->cam.x_step, (float)x + 0.5),
						scale(scene->cam.y_step,
							scene->window.h - (float)y + 0.5)));
			ray = normalize(subtract(ray, scene->cam.eye));
			mlx_put_pixel(img, x, y, trace(scene, ray));
		}
	}
}
