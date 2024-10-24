#include "../inc/ray_tracer.h"

typedef struct s_projectile
{
	t_tuple *position;
	t_tuple *velocity;
} t_projectile;

typedef struct s_environment
{
	t_tuple *gravity;
	t_tuple *wind;
} t_environment;

uint32_t	ft_colour_to_uint32(t_colour *colour)
{
	uint32_t color;

	color = 0;
	color =  (uint32_t)(0xFF) << 24;
	color |= ((uint32_t)(colour->b * 255.0) & 0xFF) << 16;
	color |= ((uint32_t)(colour->g * 255.0) & 0xFF) << 8;
	color |= ((uint32_t)(colour->r * 255.0) & 0xFF);
	return (color);
}

void	ft_color_screen(mlx_image_t *img, uint32_t colour)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINSIZE)
	{
		x = 0;
		while (x < WINSIZE)
		{
			((uint32_t *)img->pixels)[y * WINSIZE + x] = colour;
			x++;
		}
		y++;
	}
}

static int	tick(t_environment *env, t_projectile *proj)
{
	t_tuple	*position;
	t_tuple	*velocity;
	t_tuple	*temp;

	temp = add(proj->velocity, env->gravity);
	if (!temp)
		return (ERROR);
	position = add(proj->position, proj->velocity);
	velocity = add(temp, env->wind);
	if (!position || !velocity)
		return (ERROR);
	proj->position = position;
	proj->velocity = velocity;
	free(temp);
	return (SUCCESS);
}

int	project_one(mlx_image_t *img)
{
	t_environment	*env;
	t_projectile	*proj;
	int				tick_count;
	t_colour		*colour;
	float			scale;

	scale = 6.05;//6.25 is visible on a ~900x900 window
	ft_color_screen(img, 0xFF000000);
	env = malloc(1 * sizeof(t_environment));
	proj = malloc(1 * sizeof(t_projectile));
	colour = create_colour(1, 0.753, 0.796);//pink
	if (!env || !proj)
		return (ERROR);
	tick_count = 0;
	proj->position = create_tuple(0, 250, 0, POINT);
	proj->velocity = multiply_tuple((create_tuple(1, 1, 0, VECTOR)), scale);
	env->gravity = create_tuple(0, -0.1, 0, VECTOR);
	env->wind = create_tuple(-0.01, 0, 0, VECTOR);
	while (proj->position->y > 0)
	{
		if (tick(env, proj) == ERROR)
			return (ERROR);
		if (proj->position->y < 0)
			break ;
		((uint32_t *)img->pixels)[(WINSIZE - (unsigned int)proj->position->y) * WINSIZE + (unsigned int)proj->position->x] = ft_colour_to_uint32(colour);
		tick_count++;
	}
	return (SUCCESS);
}
