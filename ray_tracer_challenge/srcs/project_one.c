#include <math.h>
#include "../inc/ray_tracer.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SUCCESS
# define SUCCESS 0
#endif
#ifndef ERROR
# define ERROR 1
#endif

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

int	project_one(void)
{
	t_environment	*env;
	t_projectile	*proj;
	int				tick_count;
	t_colour		**canvas;
	t_colour		*color;

	color = malloc(1 * sizeof(t_colour));
	env = malloc(1 * sizeof(t_environment));
	proj = malloc(1 * sizeof(t_projectile));
	color = create_colour(0.3, 1, 1);
	if (!env || !proj)
		return (ERROR);
	tick_count = 0;
	proj->position = create_tuple(0, 1, 0, POINT);
	proj->velocity = multiply_tuple((create_tuple(1, 1, 0, VECTOR)), 1.25);
	env->gravity = create_tuple(0, -0.1, 0, VECTOR);
	env->wind = create_tuple(-0.01, 0, 0, VECTOR);

	canvas = create_canvas(90, 55);
	while (proj->position->y > 0)
	{
		if (tick(env, proj) == ERROR)
			return (ERROR);
		ft_tuple_print(proj->position);
		write_pixel(canvas, proj->position->x, 55 - proj->position->y, color);
		tick_count++;
	}
	canvas_to_ppm("project1.ppm", canvas, 90, 55);
	printf("Projectile has landed after %d ticks at:\n", tick_count);
	ft_tuple_print(proj->position);
	// free(proj->position);
	// free(proj->velocity);
	return (SUCCESS);
}
