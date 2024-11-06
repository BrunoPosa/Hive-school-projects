#include "../ray_tracer_challenge/inc/ray_tracer.h"
#include "../file_to_list/inc/file_to_list.h"
#include "../MLX42/include/MLX42/MLX42.h"

/*
	Struct t_function is a stupid test of using function pointers
	to switch between functions when rendering different objects
*/
typedef struct s_function
{
	int		(*circle)(int x, int y, int center, int radius);
	int		(*sphere)(float x, float y, float center, float radius);
} t_function;

void	map_coordinates(float *x, float *y, int wsize);
int 	render_pixels(mlx_image_t *img, t_function f);
int		circle(int x, int y, int center, int radius);
int		sphere_intersect(float x, float y, float center, float radius);
int		color_sphere(float z);

void	map_coordinates(float *x, float *y, int wsize)
{
	int i = 0;
	while (i < wsize)
	{
		x[i] = (2.0f * i / (wsize - 1)) - 1.0f;;
		y[i] = (2.0f * i / (wsize - 1)) - 1.0f;;
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

int	color_sphere(float z)
{
	return (((int)(z*70) << 24 | (int)(z*50) << 16 | 22 << 8 | 255));
}

/*
	x and y are the normalized coordinates of the pixel on the screen.
	x and y are also members of the camera's ray.
*/
int	sphere_intersect(float x, float y, float center, float radius)
{
	float camera_z = -1.732;
	t_tuple *ray_origin = create_tuple(0, 0, camera_z, 1);
	t_tuple *sphere_center = create_tuple(center, center, 0.5, 1);
	t_tuple *ray_direction = create_tuple(x, y, -0.5, 0);
	
	t_tuple *ray_origin_to_sphere_center = subtract(ray_origin, sphere_center);
	float a = dot(ray_direction, ray_direction);
	float b = 2 * dot(ray_direction, ray_origin_to_sphere_center);
	float c = dot(ray_origin_to_sphere_center, ray_origin_to_sphere_center) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0x00000000);
	else
		return (color_sphere(-b + sqrt(discriminant) / (2 * a)));
}

int	render_pixels(mlx_image_t *img, t_function f)
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
			((uint32_t *)img->pixels)[(WINSIZE - j) * WINSIZE + i] = f.sphere(x[i], y[j], 0, 1); // f.circle(x, y, 500, 300);
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
	
	t_function function = {	circle,
							sphere_intersect};
	render_pixels(img, function);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return(SUCCESS);
}
