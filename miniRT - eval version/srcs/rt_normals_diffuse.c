/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_normals_diffuse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:57:56 by bposa             #+#    #+#             */
/*   Updated: 2024/12/26 03:58:35 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static bool	is_point_inside_cyl(t_vec point, t_shape *cyl)
{
	t_vec	projection;
	t_vec	base_to_ray_orig;
	float	distance_to_axis;
	float	projection_len;

	ft_memset(&projection, 0, sizeof(t_vec));
	base_to_ray_orig = subtract(point, cyl->xyz);
	distance_to_axis = 0.0;
	projection_len = dot(base_to_ray_orig, cyl->axis);
	if (projection_len < 0 || projection_len > cyl->h)
		return (0);
	projection = add(cyl->xyz, scale(cyl->axis, projection_len));
	distance_to_axis = magnitude(subtract(point, projection));
	if (distance_to_axis > cyl->r)
		return (0);
	return (1);
}

/*
	returns normalized surface normal of cylinder
*/
static t_vec	cyl_normal(t_raydata *rayd, t_shape *cyl)
{
	t_vec	base_to_hitp;
	t_vec	projection;
	float	projection_len;

	base_to_hitp = create_vec(0, 0, 0);
	projection = create_vec(0, 0, 0);
	projection_len = 0.0;
	if (cyl->part_hit == top)
		return (cyl->axis);
	else if (cyl->part_hit == bottom)
		return (negate(cyl->axis));
	base_to_hitp = subtract(rayd->hitp, cyl->xyz);
	projection_len = dot(base_to_hitp, cyl->axis);
	projection = scale(cyl->axis, projection_len);
	return (normalize(subtract(rayd->hitp, add(cyl->xyz, projection))));
}

static bool	is_backlit(t_scene *scene, t_shape *plane, t_raydata *rayd)
{
	if ((dot(plane->axis, rayd->shadow_ray) < 0
			&& dot(plane->axis, subtract(scene->cam.eye, rayd->hitp)) > 0)
		|| (dot(plane->axis, rayd->shadow_ray) > 0
			&& dot(plane->axis, subtract(scene->cam.eye, rayd->hitp)) < 0))
		return (true);
	return (false);
}

/*
	Used to shade surface of lit side of shape. Returns colour of shape scaled by
	light brightness and diffuse amount (smaller if surface normal is angled away)
	Returns black (no contribution) if light and surface normal angle >= 90 deg,
	and in special case when camera is in/below a shape and the light is outside.
*/
t_rgb	calc_diffuse_part(t_scene *scene, t_shape *shape, t_raydata *rayd)
{
	t_rgb	color;
	float	diffuse_amount;
	float	light_distance;

	color = black();
	diffuse_amount = 0.0;
	light_distance = magnitude(subtract(scene->lightxyz, shape->xyz));
	if ((shape->type == sphere && shape->inside && light_distance > shape->r)
		|| (shape->type == plane && is_backlit(scene, shape, rayd) == true)
		|| (shape->type == cylinder && shape->inside
			&& is_point_inside_cyl(scene->lightxyz, shape) == false))
		return (black());
	color = scale_colour(shape->rgb, scene->lbr);
	diffuse_amount = dot(rayd->normal, rayd->shadow_ray);
	if (diffuse_amount < EPSILON && shape->type != plane)
		return (black());
	else if (shape->type == plane)
		diffuse_amount = fabs(diffuse_amount);
	return (scale_colour(color, diffuse_amount));
}

t_vec	surface_normal(t_scene *scene, t_shape *shape, t_raydata *rayd)
{
	if (shape->type == plane)
		return (shape->axis);
	else if (shape->type == sphere && shape->inside == true)
		return (negate(normalize(subtract(rayd->hitp, shape->xyz))));
	else if (shape->type == sphere && shape->inside == false)
		return (normalize(subtract(rayd->hitp, shape->xyz)));
	else
	{
		if (is_point_inside_cyl(scene->cam.eye, shape) == true)
		{
			shape->inside = true;
			return (negate(cyl_normal(rayd, rayd->shape)));
		}
		else
			return (cyl_normal(rayd, rayd->shape));
	}
}
