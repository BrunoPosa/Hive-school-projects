/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/11/23 16:56:21 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

void	map_coordinates(float *x, float *y, int wsize)
{
	int 	i;
	float	new_wsize;

	i = 0;
	new_wsize = 2.0f;
	while (i < wsize)
	{
		x[i] = i * new_wsize / wsize - (new_wsize / 2);
		y[i] = i * new_wsize / wsize - (new_wsize / 2);
		i++;
	}
}
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

int	color_sphere(float n)
{
	return ((clamp(n * 100) << 24 | clamp(n * 100) << 16 | clamp(n * 100) << 8 | 255));
}

int clamp(float n)
{
	if (n > 255)
		return 255;
	if (n < 0)
		return 0;
	return n;
}

t_tuple *calculate_hit_point(t_tuple *ray, float t)
{
	t_tuple *scaled_direction = multiply_tuple(ray, t);
	t_tuple *hit_point = add(ray, scaled_direction);
	free(scaled_direction);

	// t_tuple *normal = calculate_sphere_normal(hit_point, create_point(SPH_X, SPH_Y, SPH_Z));
	// hit_point = add(hit_point, multiply_vec_by_scalar(normal, 0.001)); // Offset by a small value

	hit_point->w = POINT;
	return (hit_point);
}

t_tuple *calculate_sphere_normal(t_tuple *hit_point, t_tuple *sphere_center)
{
	t_tuple *normal = subtract(hit_point, sphere_center);
	t_tuple *normalized_normal = normalize(normal);
	free(normal);
	return (normalized_normal);
}



/*
color Trace(const Ray &ray, int depth) 
{ 
	Object *object = NULL; 
	float minDistance = INFINITY;
	Point pHit; 
	Normal nHit; 
	for (int k = 0; k < objects.size(); ++k) { 
		if (Intersect(objects[k], ray, &pHit, &nHit)) { 
			float distance = Distance(ray.origin, pHit); 
			if (distance < minDistance) { 
				object = objects[k];
				minDistance = distance;
			} 
		} 
	} 
	if (object == NULL) 
		return backgroundColor; // Returning a background color instead of 0

	} else if (!object->isGlass) {
		// Compute illumination only if object is not in shadow
		Ray shadowRay; 
		shadowRay.origin = pHit + nHit * bias; // Adding a small bias to avoid self-intersection
		shadowRay.direction = Normalize(lightPosition - pHit); 
		bool isInShadow = false; 
		for (int k = 0; k < objects.size(); ++k) { 
			if (Intersect(objects[k], shadowRay)) { 
				isInShadow = true; 
				break; 
			} 
		} 
		if (!isInShadow) {
			return object->color * light.brightness; // point is illuminated
		}
	} 
	return backgroundColor; // Return background color if no interaction
} 
*/


/* v0.2 of sphere intersection function */
float fsphere(t_tuple *ray, t_tuple *ray_origin, t_shape sphere)
{
	float radius = sphere.sd / 2;
	t_tuple *ray_origin_to_sphere_center = subtract(ray_origin, &sphere.xyz);
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

t_colour	*calculate_lit_side_color(t_tuple *ray, t_scene *scene, t_shape *obj, float t)
{
	t_tuple		*hitpoint;
	t_tuple		*shadow_ray;
	t_colour	*diffuse_color;
	float		diffuse_amount;

	diffuse_color = NULL;
	diffuse_amount = 0;
	hitpoint = multiply_tuple(ray, t);
	hitpoint->w = POINT;
	shadow_ray = normalize(subtract(&scene->lightpos, hitpoint));
	if (!shadow_ray)
		return (NULL);
	diffuse_amount = dot(normalize(subtract(hitpoint, &obj->xyz)), shadow_ray);
	if (diffuse_amount < 0)
		diffuse_amount = 0;
	diffuse_color = multiply_colour_by(multiply_colour_by(&obj->rgb, scene->lbr), diffuse_amount);
	return (diffuse_color);
}

int	is_in_shadow(t_tuple *shadow_ray, t_scene *scene, t_tuple *hitpoint, t_shape *obj)
{
	float		t;
	float		tmin;
	int			i;

	i = 0;
	tmin = (float)INT16_MAX;
	while (i < scene->n_sphere + scene->n_plane + scene->n_cylinder)
	{
		if (obj != &scene->shapes[i])
		{
			t = shape_intersect(shadow_ray, hitpoint, scene->shapes[i]);
			if (t > 0)
			{
				if (t <= tmin)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

float	shape_intersect(t_tuple *ray, t_tuple *ray_origin, t_shape shape)
{
	if (shape.type == sphere)
		return (fsphere(ray, ray_origin, shape));
	return (0);
}

/*
	t represents the distance along the ray from its origin where it intersects the sphere:
	t>0 means there is an intersection, and the ray hits the sphere at t units from the ray origin
*/
int	trace(t_tuple *ray, t_scene *scene, t_tuple *camera)
{
	t_shape		*obj;
	t_tuple		*shadow_ray;
	int			tmp;
	t_colour	*shade_color;
	t_colour	*diffuse_color;
	t_tuple		*hitpoint;
	float	t = 0;
	float tmin;
	int i = 0;
	tmp = 0;
	obj = NULL;
	shadow_ray = NULL;
	hitpoint = NULL;
	tmin = (float)INT16_MAX;
	shade_color = NULL;
//look for closest object's distance t, and calculate its color to return
	while (i < scene->n_sphere + scene->n_plane + scene->n_cylinder)
	{
		t = shape_intersect(ray, camera, scene->shapes[i]);
		if (t > 0 && t < tmin)
		{
			tmin = t;
			obj = &scene->shapes[i];
		}
		i++;
	}
	if (!obj)
		return (ft_colour_to_uint32(&scene->ambiant));//if no object is hit, return background color
	shade_color = hadamard_product(&obj->rgb, &scene->ambiant);
	if (!shade_color)
		return (free(shadow_ray), ERROR);
	hitpoint = multiply_tuple(ray, tmin);
	hitpoint->w = POINT;
	shadow_ray = normalize(subtract(&scene->lightpos, hitpoint));
	if (!shadow_ray)
		return (ERROR);
//with the t and obj, check if the hitpoint is in shadow by casting a ray from the hitpoint to the light source and cycling through
// all objects for intersection. if in shadow, return shape_ambient_blend(?)
	tmp = is_in_shadow(shadow_ray, scene, hitpoint, obj);
	if (tmp == 1)
		return (ft_colour_to_uint32(shade_color));
	else if (tmp == -1)
		return (free(shadow_ray), ERROR);

//if hitpoint is NOT in shadow, shade the lit side of the object using normal
	diffuse_color = calculate_lit_side_color(ray, scene, obj, tmin);
	if (!diffuse_color)
		return (free(shadow_ray), ERROR);
	return (ft_colour_to_uint32(add_colours(shade_color, diffuse_color)));//are we adding object's color twice? once in shade_color and once in diffuse_color?
}


/*
	here we remap WINSIZE onto a custom size (-2 to 2) geometric viewing plane.
	as the viewing plane is focal_length away from camera's view point,
		we add focal_length to camera's z when making the camera's ray
*/
int	render_pixels(mlx_image_t *img, t_scene *scene)
{
	float	*x = ft_calloc(WINSIZE, sizeof(float));
	float	*y = ft_calloc(WINSIZE, sizeof(float));
	int		i = 0;
	int		j = 0;
	t_tuple	*camera;

	camera = create_point(scene->camera.xyz.x, scene->camera.xyz.y, scene->camera.xyz.z);
	if (!x || !y || !camera)
		return (free(x), free(y), ERROR);
	map_coordinates(x, y, WINSIZE);
	while (i < WINSIZE)
	{
		j = 0;
		while (j < WINSIZE)
		{
			//the following lines until trace() can be t_tuple *calculate_camera_ray(t_scene *scene, t_tuple *camera, int x, int y)
			t_tuple	*ray;
			t_tuple	*ray_viewplane;
			ray_viewplane = create_point(x[i], y[WINSIZE - j], camera->z + scene->camera.focal_length);
			if (!ray_viewplane)
				return (free(x), free(y), free(camera), ERROR);
			ray = subtract(ray_viewplane, camera);
			if (!ray)
				return (free(x), free(y), free(camera), free(ray_viewplane), ERROR);
			ray = normalize(ray);
			if (!ray)
				return (free(x), free(y), free(camera), free(ray_viewplane), ERROR);
			
			((uint32_t *)img->pixels)[j * WINSIZE + i] = trace(ray, scene, camera);
			j++;
		}
		i++;
	}
	free(x);
	free(y);
	return (SUCCESS);
}
