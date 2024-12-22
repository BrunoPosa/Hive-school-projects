/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/12/22 14:21:36 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

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
			sphere->inside = TRUE;
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

bool	is_point_inside_cyl(t_vec point, t_shape *cyl)
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
t_vec	cyl_normal(t_data *raydata, t_shape *cyl)
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
	base_to_hitp = subtract(raydata->hitp, cyl->xyz);
	projection_len = dot(base_to_hitp, cyl->axis);
	projection = scale(cyl->axis, projection_len);
	return (normalize(subtract(raydata->hitp, add(cyl->xyz, projection))));
}

/*
	Used to shade surface of lit side of shape. Returns colour of shape scaled by
	light brightness and diffuse amount (smaller if surface normal is angled away)
	Returns black (no contribution) if light and surface normal angle >= 90 deg,
	and when camera is inside and the light is blocked (spheres or cylinders).
*/
t_colour	calc_diffuse_part(t_scene *scene, t_shape *shape, t_data *raydata)
{
	t_colour	color;
	float		diffuse_amount;
	float		light_distance;

	color = black();
	diffuse_amount = 0.0;
	light_distance = magnitude(subtract(scene->lightxyz, shape->xyz));
	if ((shape->type == sphere && shape->inside && light_distance > shape->r) ||
		(shape->type == cylinder && shape->inside &&
		is_point_inside_cyl(scene->lightxyz, shape) == FALSE))
		return black();
	color = scale_colour(shape->rgb, scene->lbr);
	diffuse_amount = dot(raydata->normal, raydata->shadow_ray);
	if (diffuse_amount < 0 && shape->type != plane)
		return (black());
	else
		diffuse_amount = fabs(diffuse_amount);
	return (scale_colour(color, diffuse_amount));
}

t_vec	surface_normal(t_scene *scene, t_shape *shape, t_data *raydata)
{
	if (shape->type == plane)
		return (shape->axis);
	else if (shape->type == sphere && shape->inside == TRUE)
		return (negate(normalize(subtract(raydata->hitp, shape->xyz))));
	else if (shape->type == sphere && shape->inside == FALSE)
		return (normalize(subtract(raydata->hitp, shape->xyz)));
	else
	{
		if (is_point_inside_cyl(scene->cam.eye, shape) == TRUE)
		{
			shape->inside = TRUE;
			return (negate(cyl_normal(raydata, raydata->shape)));
		}
		else
			return (cyl_normal(raydata, raydata->shape));
	}
}

bool	in_shadow(t_scene *scene, t_data *raydata)
{
	int			i;
	float		hit;
	float		distance;
	float		light_distance;

	i = 0;
	hit = 0.0;
	light_distance = magnitude(subtract(scene->lightxyz, raydata->hitp));
	distance = light_distance;
	while (i < scene->shape_count)
	{
		if (raydata->shape != &scene->shapes[i])//should we be avoiding self comparisons
		{
			hit = intersect_all(raydata->shadow_ray, raydata->hitp, &scene->shapes[i]);
			if (hit > EPSILON && hit < distance)
				distance = hit;
		}
		i++;
	}
	if (distance < light_distance)
		return (1);
	return (0);
}

//should we set shape pointer to NULL here?
float	intersect_all(t_vec ray, t_vec origin, t_shape *shape)
{
	if (shape->type == sphere)
		return (fsphere(ray, origin, shape));
	else if (shape->type == plane)
		return (fplane(ray, origin, shape));
	else
		return (fcylinder(ray, origin, shape));
}

/*
	returns 1 if ray hits a shape, sets raydata's hitmin (min hit distance)
	and shape pointer to the closest shape. If no shapes intersected, returns 0
*/
bool	closest_shape_hit(t_scene *scene, t_vec ray, t_data *raydata)
{
	float	hit;
	int		i;

	hit = 0.0f;
	i = 0;
	raydata->hitmin = INFINITY;
	while (i < scene->shape_count)
	{
		hit = intersect_all(ray, scene->cam.eye, &scene->shapes[i]);
		if (hit >= EPSILON && hit < raydata->hitmin)
		{
			raydata->hitmin = hit;
			raydata->shape = &scene->shapes[i];
		}
		i++;
	}
	if (raydata->hitmin < INFINITY)
		return (1);
	return (0);
}

/*
	Sends ray interacting through scene, returns computed uint_32 color for pixel
*/
int trace(t_scene *scene, t_vec ray)
{
	t_data	raydata;

	ft_memset(&raydata, 0, sizeof(t_data));
	if (!closest_shape_hit(scene, ray, &raydata))
		return(to_uint32(scene->ambiant));
	raydata.hitp = add(scene->cam.eye, scale(ray, raydata.hitmin));
	raydata.shadow_ray = normalize(subtract(scene->lightxyz, raydata.hitp));
	raydata.base_color = hadamard_product(raydata.shape->rgb, scene->ambiant);
	if (in_shadow(scene, &raydata))
		return(to_uint32(raydata.base_color));
	raydata.normal = surface_normal(scene, raydata.shape, &raydata);
	raydata.diffuse_part = calc_diffuse_part(scene, raydata.shape, &raydata);
	return (to_uint32(add_colours(raydata.base_color, raydata.diffuse_part)));
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
			ray = add(corner, add(scale(scene->cam.x_step, (float)x + 0.5f),
				scale(scene->cam.y_step, scene->window.h - (float)y + 0.5f)));
			ray = normalize(subtract(ray, scene->cam.eye));
			((uint32_t *)img->pixels)[y * scene->window.w + x] = trace(scene, ray);//use safer mlx_put_pixel instead
		}
	}
}
