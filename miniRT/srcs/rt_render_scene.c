/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/12/17 19:48:40 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int clamp(float n)
{
	if (n > 255)
		return 255;
	if (n < 0)
		return 0;
	return n;
}

/*
	-'a' of the quadratic formula is 1, as 'ray' is a normalized vector, so we leave it out
*/
float fsphere(t_vec ray, t_vec origin, t_shape *sphere)
{
	t_vec origin_to_sphere_center;
	float	t;
	float	b;
	float	c;
	float	discriminant;

	origin_to_sphere_center = subtract(origin, sphere->xyz);
	t = -1.0f;
	b = 2 * dot(ray, origin_to_sphere_center);
	c = dot(origin_to_sphere_center, origin_to_sphere_center) - sphere->r * sphere->r;
	discriminant = b * b - 4 * c;
	if (discriminant < 0)
		return (-1);
	t = (-b - sqrt(discriminant)) / 2;
	if (t < EPSILON)
	{
		t = (-b + sqrt(discriminant)) / 2;
		if (t > EPSILON)
			sphere->part_hit = inside;
	}
	return (t);
}

float	fplane(t_vec ray, t_vec origin, t_shape *plane)
{
	t_vec	origin_to_plane;
	float	dividend;
	float	divisor;
	float	t;

	origin_to_plane = subtract(plane->xyz, origin);
	dividend = dot(plane->axis, origin_to_plane);
	divisor = dot(ray, plane->axis);
	if (fabs(divisor) < EPSILON)
		return (-1);
	t = dividend / divisor;
	if (t < EPSILON)
		return (-1);
	return (t);
}

float	intersect_cyl_caps(t_vec ray, t_vec origin, t_shape *cyl)
{
	t_shape	cap;
	t_shape	base;
	float	t_top;
	float	t_base;

	cap = *cyl;
	base = *cyl;
	cap.xyz = add(cyl->xyz, scale(cyl->axis, cyl->h));
	base.axis = negate(cyl->axis);
	t_top = cyl_radius_check(ray, origin, fplane(ray, origin, &cap), &cap);
	t_base = cyl_radius_check(ray, origin, fplane(ray, origin, &base), &base);
	if (t_top > EPSILON && (t_base < EPSILON || t_top < t_base))
	{
		cyl->part_hit = top;
		return (t_top);
	}
	else
	{
		cyl->part_hit = bottom;
		return (t_base);
	}
}

/*
	Returns minimum positive distance t if ray intersects the cylinder;
	Sets 'shape->part_hit' to top, bottom, or body. Returns < 0 if ray misses.
*/
float fcylinder(t_vec ray, t_vec origin, t_shape *cyl)
{
	t_vec	oc;
	float	coef[3];
	float	discriminant;
	float	t;
	float	tcaps;

	oc = subtract(origin, cyl->xyz);
	coef[a] = dot(ray, ray) - (pow(dot(ray, cyl->axis), 2));
	coef[b] = 2 * (dot(ray, oc) - (dot(ray, cyl->axis) * dot(oc, cyl->axis)));
	coef[c] = dot(oc, oc) - pow(dot(oc, cyl->axis), 2) - cyl->r * cyl->r;
	discriminant = coef[b] * coef[b] - 4 * coef[a] * coef[c];
	if (discriminant < 0)
		return (-1);
	t = (-coef[b] - sqrt(discriminant)) / (2 * coef[a]);
	if (t < EPSILON)
		t = (-coef[b] + sqrt(discriminant)) / (2 * coef[a]);
	t = cyl_height_check(ray, origin, t, cyl);
	tcaps = intersect_cyl_caps(ray, origin, cyl);
	if (t > EPSILON && (tcaps < EPSILON || t < tcaps))
	{
		cyl->part_hit = body;
		return (t);
	}
	return (tcaps);
}

bool	is_cam_inside_cyl(t_vec point, t_shape *cyl)
{
	t_vec	projection;
	t_vec	base_to_ray_orig;
	float	projection_len;
	float	distance_to_axis;

	distance_to_axis = 0.0;
	projection = create_vec(0,0,0);
	base_to_ray_orig = subtract(point, cyl->xyz);
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
t_vec	cyl_normal(t_data *ray_data, t_shape *cyl)
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
	base_to_hitp = subtract(ray_data->hitp, cyl->xyz);
	projection_len = dot(base_to_hitp, cyl->axis);
	projection = scale(cyl->axis, projection_len);
	return (normalize(subtract(ray_data->hitp, add(cyl->xyz, projection))));
}

/*
	Used to approximate surface shading of lit side	of shape. Unless a plane,
	it returns 0,0,0 if angle between light and surface normal is >= 90 degrees
*/
t_colour	diffuse_colour(t_scene *scene, t_shape *shape, t_data *ray_data)
{
	t_colour	color;
	float		diffuse_amount;
 
	color = scale_colour(shape->rgb, scene->lbr);
	diffuse_amount = dot(ray_data->normal, ray_data->shadow_ray);
	if (shape->type == plane)
		diffuse_amount = fabs(diffuse_amount);
	if (diffuse_amount < 0)
		diffuse_amount = 0;
	return (scale_colour(color, diffuse_amount));
}

t_vec	surface_normal(t_scene *scene, t_shape *shape, t_data *ray_data)
{
	if (shape->type == plane)
		return (shape->axis);
	else if (shape->type == sphere && shape->part_hit == inside)
		return (negate(normalize(subtract(ray_data->hitp, shape->xyz))));
	else if (shape->type == sphere)
		return (normalize(subtract(ray_data->hitp, shape->xyz)));
	else if (is_cam_inside_cyl(scene->cam.eye, ray_data->shape) == TRUE)
		return (negate(cyl_normal(ray_data, ray_data->shape)));
	return (cyl_normal(ray_data, ray_data->shape));
}

bool	in_shadow(t_scene *scene, t_data *ray_data)
{
	float		hit;
	float		distance;
	int			i;
	float		light_distance;

	i = 0;
	light_distance = magnitude(subtract(scene->lightxyz, ray_data->hitp));
	distance = light_distance;
	while (i < scene->shape_count)
	{
		if (ray_data->shape != &scene->shapes[i])//should we be avoiding self comparisons
		{
			hit = intersect(ray_data->shadow_ray, ray_data->hitp, &scene->shapes[i]);
			if (hit >= EPSILON && hit < distance)
				distance = hit;
		}
		i++;
	}
	if (distance < light_distance)
		return (1);
	return (0);
}

float	intersect(t_vec ray, t_vec origin, t_shape *shape)
{
	if (shape->type == sphere)
		return (fsphere(ray, origin, shape));
	else if (shape->type == plane)
		return (fplane(ray, origin, shape));
	else
		return (fcylinder(ray, origin, shape));
}

/*
	returns 1 if ray hits a shape, sets ray_data's hitmin (min hit distance)
	and shape pointer to the closest shape. If no shapes intersected, returns 0
*/
bool	closest_shape_hit(t_scene *scene, t_vec ray, t_data *ray_data)
{
	float	hit;
	int		i;

	hit = 0.0f;
	i = 0;
	ray_data->hitmin = INFINITY;
	while (i < scene->shape_count)
	{
		hit = intersect(ray, scene->cam.eye, &scene->shapes[i]);
		if (hit >= EPSILON && hit < ray_data->hitmin)
		{
			ray_data->hitmin = hit;
			ray_data->shape = &scene->shapes[i];
		}
		i++;
	}
	if (ray_data->hitmin < INFINITY)
		return (1);
	return (0);
}

/*
	Sends ray interacting through scene, returns computed uint_32 color for pixel
*/
int trace(t_scene *scene, t_vec ray)
{
	t_data	ray_data;

	ft_memset(&ray_data, 0, sizeof(t_data));
	if (!closest_shape_hit(scene, ray, &ray_data))
		return(to_uint32(scene->ambiant));
	ray_data.hitp = add(scene->cam.eye, scale(ray, ray_data.hitmin));
	ray_data.shadow_ray = normalize(subtract(scene->lightxyz, ray_data.hitp));
	ray_data.base_color = hadamard_product(ray_data.shape->rgb, scene->ambiant);
	if (in_shadow(scene, &ray_data))
		return(to_uint32(ray_data.base_color));
	ray_data.normal = surface_normal(scene, ray_data.shape, &ray_data);
	ray_data.diffuse_part = diffuse_colour(scene, ray_data.shape, &ray_data);
	return (to_uint32(add_colours(ray_data.base_color, ray_data.diffuse_part)));
}

/*
	img.pixels buffer will display pixels in order from top left to bottom right
	so we invert the y axis to start bottom left like a cartesian coordinate sys.
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
	while (++x < scene->viewplane_width)
	{
		y = -1;
		while (++y < scene->viewplane_height)
		{
			ray = add(corner, add(scale(scene->cam.x_step, x),
				scale(scene->cam.y_step, scene->viewplane_height - y)));
			ray = normalize(subtract(ray, scene->cam.eye));
			((uint32_t *)img->pixels)[y * scene->viewplane_width + x] = trace(scene, ray);
		}
	}
}
