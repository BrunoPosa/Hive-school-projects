/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:23 by bposa             #+#    #+#             */
/*   Updated: 2024/11/16 22:41:08 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// void	render_scene(t_rt rt)
// {
// 	t_render	r;

// 	r.y = -1;
// 	while (++r.y < rt.height)
// 	{
// 		r.x = -1;
// 		while (++r.x < rt.width)
// 		{

// 		}
// 	}
// }


#include "../ray_tracer_challenge/inc/ray_tracer.h"
#include "../file_to_list/inc/file_to_list.h"

#define SPH_X 0
#define SPH_Y 0
#define SPH_Z 2
//light purpleish pinkish 0xFFC673FF
#define SP_R 198
#define SP_G 115
#define SP_B 255

#define CAM_X 0
#define CAM_Y 0
#define CAM_Z 0

#define LIG_X 0
#define LIG_Y 10
#define LIG_Z 2

t_tuple *multiply_vec_by_scalar(t_tuple *vec, float scalar);
void	map_coordinates(float *x, float *y, int wsize);
int 	render_pixels(mlx_image_t *img);
int		circle(int x, int y, int center, int radius);
int		sphere_intersect(float x, float y, float center, float radius);
int		color_sphere(float z);
float	fsphere(t_tuple *ray, t_tuple *ray_origin);
t_tuple *calculate_sphere_normal(t_tuple *hit_point, t_tuple *sphere_center);
int		trace(t_tuple *ray);
int clamp(float n);

void	map_coordinates(float *x, float *y, int wsize)
{
	int i = 0;
	while (i < wsize)
	{
		x[i] = i * 2.0f / wsize - 1.0f;
		y[i] = i * 2.0f / wsize - 1.0f;
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
	return ((clamp(n * SP_R) << 24 | clamp(n * SP_G) << 16 | clamp(n * SP_B) << 8 | 255));
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

    } else if (!object->isGlass) { // Check if object is not glass (diffuse/opaque)
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
 
// Render loop for each pixel of the image
for (int j = 0; j < imageHeight; ++j) { 
    for (int i = 0; i < imageWidth; ++i) { 
        Ray primRay; 
        computePrimRay(i, j, &primRay); // Assume computePrimRay correctly sets the ray origin and direction
        pixels[i][j] = Trace(primRay, 0); 
    } 
}
*/



/* v0.2 of sphere intersection function */
float fsphere(t_tuple *ray, t_tuple *ray_origin)
{
	float radius = 0.5;
	t_tuple *sphere_center = create_point(SPH_X, SPH_Y, SPH_Z);
	t_tuple *ray_origin_to_sphere_center = subtract(ray_origin, sphere_center);
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


int	trace(t_tuple *ray)
{
	t_tuple	*lightpos = create_point(LIG_X, LIG_Y, LIG_Z);
	t_tuple *hitpoint;
	float	t;

	hitpoint = NULL;
	t = fsphere(ray, create_point(CAM_X, CAM_Y, CAM_Z));//camera origin point
	if (t <= 0)
		return (0xFFFFFFFF);// bg

	hitpoint = multiply_tuple(ray, t);//this was causing problems with sphere -light orientations..
	hitpoint->w = POINT;// this, too

	t_tuple	*shadow_ray = normalize(subtract(lightpos, hitpoint));
	shadow_ray->w = VECTOR;
	t_tuple	*normal = normalize(subtract(hitpoint, create_point(SPH_X, SPH_Y, SPH_Z)));
	float lit = dot(normal, shadow_ray);
	if (lit <= 0)
		return (0xFF000000);
	return (color_sphere(lit));
}


int	render_pixels(mlx_image_t *img)
{
	float	*x = ft_calloc(WINSIZE, sizeof(float));
	float	*y = ft_calloc(WINSIZE, sizeof(float));
	int		i = 0;
	int		j = 0;

	if (!x || !y)
		return (free(x), free(y), ERROR);
	map_coordinates(x, y, WINSIZE);
	while (i < WINSIZE)
	{
		j = 0;
		while (j < WINSIZE)
		{
			//viewing plane is focal length away from camera's view point
			float focal_len = 1.732;
			t_tuple *ray = normalize(subtract(create_vector(x[i], y[WINSIZE - j], CAM_Z + focal_len), create_vector(CAM_X, CAM_Y, CAM_Z)));
			((uint32_t *)img->pixels)[j * WINSIZE + i] = trace(ray);
			j++;
		}
		i++;
	}
	free(x);
	free(y);
	return (SUCCESS);
}
