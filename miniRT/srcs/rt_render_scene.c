/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/12/08 17:50:27 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	circle(int x, int y, int center, int radius)
{
	int dx = x - center;
	int dy = y - center;
	int distance = sqrt(dx * dx + dy * dy);
	if (distance < radius)
		return (0xFFFF0000);
	else
		return (0x00000000);
}

int clamp(float n)
{
	if (n > 255)
		return 255;
	if (n < 0)
		return 0;
	return n;
}

/*
	v0.2 of sphere intersection function
*/
float fsphere(t_vec ray, t_vec ray_origin, t_shape sphere)
{
	float radius = sphere.sd / 2;
	t_vec ray_origin_to_sphere_center = subtract(ray_origin, sphere.xyz);
	float a = dot(ray, ray);
	float b = 2 * dot(ray, ray_origin_to_sphere_center);
	float c = dot(ray_origin_to_sphere_center, ray_origin_to_sphere_center) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	float t1 = (-b - sqrt(discriminant)) / (2 * a);
	float t2 = (-b + sqrt(discriminant)) / (2 * a);
	//this is also different now, returning the positive despite a negative being smaller
	if (t1 > EPSILON && t2 > EPSILON)
		return fminf(t1, t2); // Return the smallest positive t
	else if (t1 > EPSILON)
		return t1;
	else if (t2 > EPSILON)
		return t2;
	return (0);
}

float	fplane(t_vec ray, t_vec ray_origin, t_shape plane)
{
	float	dividend;
	float	divisor;
	float	t;
	t_vec	origin_to_plane;

	dividend = 0.0;
	divisor = 0.0;
	origin_to_plane = subtract(plane.xyz, ray_origin);
	dividend = dot(plane.xyz3d, origin_to_plane);
	divisor = dot(ray, plane.xyz3d);
	if (fabs(divisor) < EPSILON)
		return (0);
	t = dividend / divisor;
	if (t < EPSILON)
		return (0);
	return (t);
}

//fix in case of planes so the surface is smootly shaded, instead of chopped like now
//fix in case of planes so there is no recalculating #efficiency.
int	calculate_diffuse_colour(t_scene *scene, t_shape *shape)
{
	float		diffuse_amount;
	t_colour	*diffuse_color;
	t_vec		normal;

	diffuse_amount = 0;
	diffuse_color = NULL;
	normal = subtract(scene->data->hitp, shape->xyz);
	scene->data->normal = normalize(normal);
	diffuse_amount = dot(scene->data->normal, scene->data->shadow_ray);
	if (shape->type == plane)
		diffuse_amount = fabs(dot(shape->xyz3d, scene->data->shadow_ray));//how do we color if plane is looking away from light/diffuse_amount < 0?
	// if (diffuse_amount < 0)
	// 	diffuse_amount = 0;
	diffuse_color = multiply_colour_by(&shape->rgb, scene->lbr);
	if (!diffuse_color)
		return (ERROR);
	scene->data->diffuse_color = multiply_colour_by(diffuse_color, diffuse_amount);
	free(diffuse_color);
	return(SUCCESS);
}

t_colour	*calculate_colour(t_scene *scene, t_shape *shape)
{
	int	in_shadow;

	in_shadow = 0;
	scene->data->shade_color = hadamard_product(&shape->rgb, &scene->ambiant);
	if (!scene->data->shade_color)
		return (NULL);
	in_shadow = shadow_check(scene, scene->data->shadow_ray, shape);
	if (scene->err_status != SUCCESS)
		return (NULL);
	if (in_shadow)
		return (scene->data->shade_color);
	else if (calculate_diffuse_colour(scene, shape) != SUCCESS)
	{
		scene->err_status = ERROR;
		return (NULL);
	}
	return (add_colours(scene->data->shade_color, scene->data->diffuse_color));
}

int	shadow_check(t_scene *scene, t_vec shadowray, t_shape *shape)
{
	float		t;
	float		tmin;
	int			i;
	float		light_distance;

	i = 0;
	light_distance = fabs(magnitude(subtract(scene->lightpos, scene->data->hitp)));
	tmin = light_distance;
	while (i < scene->shape_count)
	{
		if (shape != &scene->shapes[i])
		{
			t = shape_intersect(shadowray, scene->data->hitp, scene->shapes[i]);
			if (t > 0)
			{
				if (t < tmin)
					tmin = t;
			}
		}
		i++;
	}
	if (tmin < light_distance)
		return (1);
	return (0);
}

float	shape_intersect(t_vec ray, t_vec ray_origin, t_shape shape)
{
	if (shape.type == sphere)
		return (fsphere(ray, ray_origin, shape));
	else if (shape.type == plane)
		return (fplane(ray, ray_origin, shape));
	return (0);
}

int	find_closest_shape(t_scene *scene, t_vec ray)
{
	float	hit;
	int		i;

	i = 0;
	hit = 0.0;
	scene->data->hitmin = (float)INT32_MAX;
	while (i < scene->shape_count && scene->err_status == SUCCESS)
	{
		hit = shape_intersect(ray, scene->camera.pos, scene->shapes[i]);
		if (hit > 0.0 && hit < scene->data->hitmin)
		{
			scene->data->hitmin = hit;
			scene->data->shape = &scene->shapes[i];
		}
		i++;
	}
	if (scene->data->shape)
		return (1);
	return (0);
}

/*
	t represents the distance along the ray from its origin where it intersects the sphere:
	t>0 means there is an intersection, and the ray hits the sphere at t units from the ray origin
*/
int trace(t_scene *scene, t_vec ray)
{
	uint32_t	colour_uint;
	t_vec		shadow_ray;

	colour_uint = 0;
	if (init_trace_data(scene) != SUCCESS)
		return (ERROR);
	if (!find_closest_shape(scene, ray))
		return(ft_colour_to_uint32(&scene->ambiant));
	shadow_ray = create_vec(0, 0, 0);
	scene->data->hitp = add(scene->camera.pos, multiply_tuple(ray, scene->data->hitmin));
	shadow_ray = subtract(scene->lightpos, scene->data->hitp);
	scene->data->shadow_ray = normalize(shadow_ray);
	colour_uint = ft_colour_to_uint32(calculate_colour(scene, scene->data->shape));
	free_data(scene->data);
	return (colour_uint);
}

/*
	as the viewing plane is focal_length away from camera's view point,
		we add focal_length to camera's z when making the camera's ray
*/
int	render_pixels(t_scene *scene, mlx_image_t *img)
{
	int		i;
	int		j;
	t_vec	ray;

	i = -1;
	j = -1;
	ray = create_vec(0, 0, 0);
	while (++i < WINSIZE)
	{
		j = -1;
		while (++j < WINSIZE)
		{
			ray = calculate_camera_ray(scene, scene->camera.pos, i, WINSIZE - j);
			if (!diff(ray, create_vec(0, 0, 0)))//do we need to check for this?
				return (ERROR);
			((uint32_t *)img->pixels)[j * WINSIZE + i] = trace(scene, ray);
		}
	}
	return (scene->err_status);
}
