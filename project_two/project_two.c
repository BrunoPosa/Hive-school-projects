#include "../ray_tracer_challenge/inc/ray_tracer.h"
#include "../file_to_list/inc/file_to_list.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define SPH_X 0
#define SPH_Y 0
#define SPH_Z 3

t_tuple *multiply_vec_by_scalar(t_tuple *vec, float scalar);
void	map_coordinates(float *x, float *y, int wsize);
int 	render_pixels(mlx_image_t *img);
int		circle(int x, int y, int center, int radius);
int		sphere_intersect(float x, float y, float center, float radius);
int		color_sphere(float z);
float	fsphere(t_tuple *ray, t_tuple *ray_origin);
t_tuple *calculate_sphere_normal(t_tuple *hit_point, t_tuple *sphere_center);
t_tuple *calculate_hit_point(t_tuple *ray, float t);
int		trace(t_tuple *ray);

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

int	color_sphere(float t)
{
	return (((int)(t*40) << 24 | (int)(t*50) << 16 | 22 << 8 | 255));
}

/*
	x and y are the normalized coordinates of the pixel on the screen.
	x and y are also members of the camera's ray.
	THIS IS v0.1 OF THE SPHERE INTERSECTION FUNCTION
*/
int	sphere_intersect(float x, float y, float center, float radius)
{
	float camera_z = -1.732;
	t_tuple *ray_origin = create_point(0, 0, camera_z);//camera point
	t_tuple *sphere_center = create_point(center, center, 0.75);
	t_tuple *ray_direction = create_vector(x, y, -0.5);
	t_tuple *ray_origin_to_sphere_center = subtract(ray_origin, sphere_center);
	float a = dot(ray_direction, ray_direction);
	float b = 2 * dot(ray_direction, ray_origin_to_sphere_center);
	float c = dot(ray_origin_to_sphere_center, ray_origin_to_sphere_center) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0x00000000);
	else
		return (color_sphere(3 * sqrt(discriminant)));
}

int	trace(t_tuple *ray)
{
	t_tuple	*lightpos = create_point(1, 20, 3);
	t_tuple *hitpoint;
	float	t;

	hitpoint = NULL;
	t = fsphere(ray, create_point(0, 0, -1.732));//camera origin point
	if (t <= 0)
		return (0xFFFFFFFF);// bg

	hitpoint = calculate_hit_point(ray, t);
	t_tuple	*shadow_ray = normalize(subtract(lightpos, hitpoint));
	shadow_ray->w = VECTOR;
	t_tuple	*normal = normalize(subtract(hitpoint, create_point(SPH_X, SPH_Y, SPH_Z)));
	float lit = dot(normal, shadow_ray);
	if (lit < 0)
		return (0xFF000000);
	// if ()
	return (color_sphere(t));//0xFF00FFFF blue
}

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
	float t = t2;
	if (t1 < t2)
		t = t1;
	// if (t < 0)
	// 	return (0);
	return (t);
}

t_tuple *multiply_vec_by_scalar(t_tuple *vec, float scalar)
{
	t_tuple *result = create_tuple(vec->x * scalar, vec->y * scalar, vec->z * scalar, vec->w * scalar);
	return (result);
}

t_tuple *calculate_hit_point(t_tuple *ray, float t)
{
	t_tuple *scaled_direction = multiply_vec_by_scalar(ray, t);
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





//camera is at (0, 0, -1.732) where -1.732 is roughly fov of 60 degrees
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
			t_tuple *ray = normalize(create_vector(x[i], y[j], 1.732));//direction = normalize((x, y, 0) - (camera_x, camera_y, camera_z)), so simply x, y, -z
			((uint32_t *)img->pixels)[(WINSIZE - j) * WINSIZE + i] = trace(ray);// f.sphere(x[i], y[j], 0, 1); // f.circle(x, y, 500, 300);
			j++;
		}
		i++;
	}
	free(x);
	free(y);
	return (SUCCESS);
}

int main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx = mlx_init(WINSIZE, WINSIZE, "circle", false);
	if (!(mlx))
		return (ERROR);
	img = mlx_new_image(mlx, WINSIZE, WINSIZE);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (mlx_terminate(mlx), ERROR);
	
	render_pixels(img);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return(SUCCESS);
}
