/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/12/15 15:34:47 by bposa            ###   ########.fr       */
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
float fsphere(t_vec ray, t_vec ray_origin, t_shape *sphere)
{
	t_vec ray_origin_to_sphere_center;
	float	t;
	float	b;
	float	c;
	float	discriminant;

	ray_origin_to_sphere_center = subtract(ray_origin, sphere->xyz);
	t = -1.0f;
	b = 2 * dot(ray, ray_origin_to_sphere_center);
	c = dot(ray_origin_to_sphere_center, ray_origin_to_sphere_center) - sphere->r * sphere->r;
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

float	fplane(t_vec ray, t_vec ray_origin, t_shape *plane)
{
	t_vec	origin_to_plane;
	float	dividend;
	float	divisor;
	float	t;

	origin_to_plane = subtract(plane->xyz, ray_origin);
	dividend = dot(plane->axis, origin_to_plane);
	divisor = dot(ray, plane->axis);
	if (fabs(divisor) < EPSILON)
		return (-1);
	t = dividend / divisor;
	if (t < EPSILON)
		return (-1);
	return (t);
}

float caps_intersect(t_vec ray, t_vec ray_origin, t_shape *cylinder)
{
	t_shape topdisc;
	t_shape bottomdisc;
	float t_top;
	float t_bottom;
	t_vec hit_point_top;
	t_vec hit_point_bottom;

	ft_bzero(&topdisc, sizeof(t_shape));
	ft_bzero(&bottomdisc, sizeof(t_shape));
	topdisc.xyz = add(cylinder->xyz, multiply_tuple(cylinder->axis, cylinder->h));
	topdisc.axis = cylinder->axis;
	bottomdisc.xyz = cylinder->xyz;
	bottomdisc.axis = negate_tuple(cylinder->axis);
	t_top = fplane(ray, ray_origin, &topdisc);
	t_bottom = fplane(ray, ray_origin, &bottomdisc);
	if (t_top > EPSILON)
	{
		hit_point_top = add(ray_origin, multiply_tuple(ray, t_top));
		if (magnitude(subtract(hit_point_top, topdisc.xyz)) > cylinder->r)
			t_top = -1;
	}
	if (t_bottom > EPSILON)
	{
		hit_point_bottom = add(ray_origin, multiply_tuple(ray, t_bottom));
		if (magnitude(subtract(hit_point_bottom, bottomdisc.xyz)) > cylinder->r)
			t_bottom = -1;
	}	
	if (t_top < EPSILON && t_bottom < EPSILON)
		return -1;
	else if (t_top > EPSILON && (t_bottom < EPSILON || t_top < t_bottom))
	{
		cylinder->part_hit = top;
		return t_top;
	}
	else
	{
		cylinder->part_hit = bottom;
		return t_bottom;
	}
}


float fcylinder(t_vec ray, t_vec ray_origin, t_shape *cylinder)
{
	t_vec	origin_to_cylinder;
	float coef[3];
	float discriminant;
	float t;
	float tcaps;
	float axis_projection;

	origin_to_cylinder = subtract(ray_origin, cylinder->xyz);
	coef[a] = dot(ray, ray) - (pow(dot(ray, cylinder->axis), 2));
	coef[b] = 2 * (dot(ray, origin_to_cylinder) - (dot(ray, cylinder->axis) *
		dot(origin_to_cylinder, cylinder->axis)));
	coef[c] = dot(origin_to_cylinder, origin_to_cylinder) - 
		pow(dot(origin_to_cylinder, cylinder->axis), 2) - cylinder->r * cylinder->r;
	discriminant = coef[b] * coef[b] - 4 * coef[a] * coef[c];
	if (discriminant < 0)
		return -1;
	t = (-coef[b] - sqrt(discriminant)) / (2 * coef[a]);
	if (t < EPSILON)
		t = (-coef[b] + sqrt(discriminant)) / (2 * coef[a]);
	if (t > EPSILON)
	{
		t_vec hit_point1 = add(ray_origin, multiply_tuple(ray, t));
		axis_projection = dot(subtract(hit_point1, cylinder->xyz), cylinder->axis);
		if (axis_projection < 0 || axis_projection > cylinder->h)
			t = -1;
	}
	tcaps = caps_intersect(ray, ray_origin, cylinder);
	if (t > EPSILON && (tcaps < EPSILON || t < tcaps))
	{
		cylinder->part_hit = body; // Body hit
		return t;
	}
	else if (tcaps > EPSILON && (t < EPSILON || tcaps < t))
		return tcaps;
	return -1;
}

int	check_cam_inside_cyl(t_vec point, t_shape *cyl)
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
	projection = add(cyl->xyz, multiply_tuple(cyl->axis, projection_len));
	distance_to_axis = magnitude(subtract(point, projection));
	if (distance_to_axis > cyl->r)
		return (0);
	cyl->part_hit = inside;
	return (1);
}

/*
	a, b, c signify which part of the cylinder was hit
	and stand for top, body, bottom. They are set in fcylinder.
*/
t_vec	calculate_cy_normal(t_data *ray_data, t_shape *cy)
{
	t_vec	base_to_hitp;
	t_vec	projection;
	float	projection_len;

	base_to_hitp = create_vec(0, 0, 0);
	projection = create_vec(0, 0, 0);
	projection_len = 0.0;
	if (cy->part_hit == top)
		return (cy->axis);
	else if (cy->part_hit == bottom)
		return (negate_tuple(cy->axis));
	base_to_hitp = subtract(ray_data->hitp, cy->xyz);
	projection_len = dot(base_to_hitp, cy->axis);
	projection = multiply_tuple(cy->axis, projection_len);
	return (normalize(subtract(ray_data->hitp, add(cy->xyz, projection))));
}

//change to void type
void	calculate_diffuse_colour(t_scene *scene, t_data *ray_data)
{
	t_colour	diffuse_color;
	float		diffuse_amount;
 
	diffuse_color = multiply_colour_by(ray_data->shape->rgb, scene->lbr);
	diffuse_amount = dot(ray_data->normal, ray_data->shadow_ray);
	if (ray_data->shape->type == plane)
		diffuse_amount = fabs(diffuse_amount);
	if (diffuse_amount < 0)
		diffuse_amount = 0;
	ray_data->diffuse_color = multiply_colour_by(diffuse_color, diffuse_amount);
}

t_colour	calculate_colour(t_scene *scene, t_data *ray_data)
{
	ray_data->shade_color = hadamard_product(ray_data->shape->rgb, scene->ambiant);
	if (shadow_check(scene, ray_data))
		return (ray_data->shade_color);
	if (ray_data->shape->type == cylinder)
	{
		ray_data->normal = calculate_cy_normal(ray_data, ray_data->shape);
		check_cam_inside_cyl(scene->cam.eye, ray_data->shape);
	}
	else if (ray_data->shape->type == plane)
		ray_data->normal = ray_data->shape->axis;
	else if (ray_data->shape->type == sphere)
		ray_data->normal = normalize(subtract(ray_data->hitp, ray_data->shape->xyz));
	if (ray_data->shape->part_hit == inside)
		ray_data->normal = negate_tuple(ray_data->normal);
	calculate_diffuse_colour(scene, ray_data);
	return (add_colours(ray_data->shade_color, ray_data->diffuse_color));
}

int	shadow_check(t_scene *scene, t_data *ray_data)
{
	float		hit;
	float		distance;
	int			i;
	float		light_distance;

	i = 0;
	light_distance = magnitude(subtract(scene->lightpos, ray_data->hitp));
	distance = light_distance;
	while (i < scene->shape_count)
	{
		if (ray_data->shape != &scene->shapes[i])//should we be avoiding self comparisons
		{
			hit = shape_intersect(ray_data->shadow_ray, ray_data->hitp, &scene->shapes[i]);
			if (hit >= EPSILON && hit < distance)
				distance = hit;
		}
		i++;
	}
	if (distance < light_distance)
		return (1);
	return (0);
}

float	shape_intersect(t_vec ray, t_vec ray_origin, t_shape *shape)
{
	if (shape->type == sphere)
		return (fsphere(ray, ray_origin, shape));
	else if (shape->type == plane)
		return (fplane(ray, ray_origin, shape));
	else
		return (fcylinder(ray, ray_origin, shape));
}

int	find_closest_hitd(t_scene *scene, t_vec ray, t_data *ray_data)
{
	float	hit;
	int		i;

	i = 0;
	hit = 0.0;
	ray_data->hitmin = INFINITY;
	while (i < scene->shape_count)
	{
		hit = shape_intersect(ray, scene->cam.eye, &scene->shapes[i]);
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
	t represents the distance along the ray from its origin where it intersects the sphere:
	t>0 means there is an intersection, and the ray hits the sphere at t units from the ray origin
*/
int trace(t_scene *scene, t_vec ray)
{
	t_data	ray_data;

	ft_memset(&ray_data, 0, sizeof(t_data));
	if (!find_closest_hitd(scene, ray, &ray_data))
		return(ft_colour_to_uint32(scene->ambiant));
	ray_data.hitp = add(scene->cam.eye, multiply_tuple(ray, ray_data.hitmin));
	ray_data.shadow_ray = normalize(subtract(scene->lightpos, ray_data.hitp));
	return (ft_colour_to_uint32(calculate_colour(scene, &ray_data)));
}

/*
	img.pixels buffer will display pixels in order from top left to bottom right
	so we invert the y axis to start bottom left like a cartesian coordinate sys.
*/
void	render_image(t_scene *scene, mlx_image_t *img)
{
	int		x;
	int		y;
	t_vec	corner;
	t_vec	ray;

	x = -1;
	y = -1;
	corner = calculate_viewplane(scene, scene->cam.eye);
	ray = create_vec(0, 0, 0);
	while (++x < WINSIZE)
	{
		y = -1;
		while (++y < WINSIZE)
		{
			ray = add(corner, add(multiply_tuple(scene->cam.x_step, x),
				multiply_tuple(scene->cam.y_step, WINSIZE - y)));
			ray = normalize(subtract(ray, scene->cam.eye));
			((uint32_t *)img->pixels)[y * WINSIZE + x] = trace(scene, ray);
		}
	}
}
