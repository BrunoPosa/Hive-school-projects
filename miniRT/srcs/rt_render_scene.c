/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/12/06 18:45:10 by bposa            ###   ########.fr       */
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
	-Returns ERROR if malloc fails
*/
float fsphere(t_tuple *ray, t_tuple *ray_origin, t_shape sphere)
{
	float radius = sphere.sd / 2;
	t_tuple *ray_origin_to_sphere_center = subtract(ray_origin, &sphere.xyz);
	if (!ray_origin_to_sphere_center)
		return (ERROR);
	float a = dot(ray, ray);
	float b = 2 * dot(ray, ray_origin_to_sphere_center);
	float c = dot(ray_origin_to_sphere_center, ray_origin_to_sphere_center) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	float t1 = (-b - sqrt(discriminant)) / (2 * a);
	float t2 = (-b + sqrt(discriminant)) / (2 * a);
	//this is also different now, returning the positive despite a negative being smaller
	if (t1 > 0 && t2 > 0)
		return fminf(t1, t2); // Return the smallest positive t
	else if (t1 > 0)
		return t1;
	else if (t2 > 0)
		return t2;
	return (0);
}

float	fplane(t_tuple *ray, t_tuple *ray_origin, t_shape plane)
{
	float	dividend;
	float	divisor;
	t_tuple	*origin_to_plane;

	dividend = 0.0;
	divisor = 0.0;
	origin_to_plane = subtract(&plane.xyz, ray_origin);
	if (origin_to_plane == NULL)
		return (ERROR);
	dividend = dot(&plane.xyz3d, origin_to_plane);
	if (dividend == ERROR)
		return (ERROR);
	divisor = dot(ray, &plane.xyz3d);
	if (divisor == ERROR)
		return (ERROR);
	// if (divisor < EPSILON)
	// 	return (-EPSILON);
	return (dividend / divisor);
}

int	shadow_check(t_scene *scene, t_tuple *shadowray, t_shape *shape)
{
	float		t;
	float		tmin;
	int			i;

	i = 0;
	tmin = (float)INT32_MAX;
	while (i < scene->shape_count && scene->err_status == SUCCESS)
	{
		if (shape != &scene->shapes[i])
		{
			t = shape_intersect(shadowray, scene->data->hitp, scene->shapes[i]);
			if (t == ERROR)
			{
				scene->err_status = ERROR;
				return (ERROR);
			}
			if (t > 0)
			{
				if (t <= tmin)
					tmin = t;
			}
		}
		i++;
	}
	if (tmin < (float)INT32_MAX)
		return (1);
	return (0);
}

float	shape_intersect(t_tuple *ray, t_tuple *ray_origin, t_shape shape)
{
	if (shape.type == sphere)
		return (fsphere(ray, ray_origin, shape));
	else if (shape.type == plane)
		return (fplane(ray, ray_origin, shape));
	return (0);
}


int	calculate_hitpoint_shadow_ray(t_scene *scene, t_tuple *ray)
{
	t_tuple		*shadow_ray;

	shadow_ray = NULL;
	scene->data->hitp = multiply_tuple(ray, scene->data->hitmin);
	if (!scene->data->hitp)
		return (ERROR);
	scene->data->hitp->w = POINT;
	shadow_ray = subtract(&scene->lightpos, scene->data->hitp);
	if (!shadow_ray)
		return (ERROR);
	scene->data->shadow_ray = normalize(shadow_ray);
	free(shadow_ray);
	if (!scene->data->shadow_ray)
		return (ERROR);
	return (SUCCESS);
}

//fix in case of planes so there is no recalculating
int	calculate_diffuse_colour(t_scene *scene, t_shape *shape)
{
	float		diffuse_amount;
	t_colour	*diffuse_color;
	t_tuple		*normal;

	diffuse_amount = 0;
	diffuse_color = NULL;
	normal = subtract(scene->data->hitp, &shape->xyz);
	if (!normal)
		return (ERROR);
	scene->data->normal = normalize(normal);
	free(normal);
	if (!scene->data->normal)
		return (ERROR);
	diffuse_amount = dot(scene->data->normal, scene->data->shadow_ray);
	if (shape->type == plane)
		diffuse_amount = dot(&shape->xyz3d, scene->data->shadow_ray);//how do we color if plane is looking away from light/diffuse_amount < 0?
	if (diffuse_amount < 0)
		diffuse_amount = 0;
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

int	find_closest_shape(t_scene *scene, t_tuple *ray)
{
	float	hit;
	int		i;

	i = 0;
	hit = 0.0;
	scene->data->hitmin = (float)INT32_MAX;
	while (i < scene->shape_count && scene->err_status == SUCCESS)
	{
		hit = shape_intersect(ray, &scene->camera.pos, scene->shapes[i]);
		if (hit == ERROR)
		{
			scene->err_status = ERROR;
			return (ERROR);
		}
		if (hit > 0 && hit < scene->data->hitmin)
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
int trace(t_scene *scene, t_tuple *ray)
{
	uint32_t	colour_uint;

	colour_uint = 0;
	if (init_trace_data(scene) != SUCCESS)
		return (ERROR);
	if (!find_closest_shape(scene, ray))
		colour_uint = ft_colour_to_uint32(&scene->ambiant);
	else if (calculate_hitpoint_shadow_ray(scene, ray) != SUCCESS)
		scene->err_status = ERROR;
	else
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
	t_tuple	*ray;

	i = -1;
	j = -1;
	ray = NULL;
	while (scene->err_status == SUCCESS && ++i < WINSIZE)
	{
		j = -1;
		while (scene->err_status == SUCCESS && ++j < WINSIZE)
		{
			ray = calculate_camera_ray(scene, &scene->camera.pos, i, WINSIZE - j);
			if (!ray)
				return (ERROR);
			((uint32_t *)img->pixels)[j * WINSIZE + i] = trace(scene, ray);
		}
	}
	free (ray);
	return (scene->err_status);
}
