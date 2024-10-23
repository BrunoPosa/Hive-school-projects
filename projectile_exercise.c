#include <math.h>
#include "ray_tracer_challenge/inc/ray_tracer.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SUCCESS
# define SUCCESS 0
#endif
#ifndef ERROR
# define ERROR 1
#endif

static t_tuple	*add_clone(t_tuple *t1, t_tuple *t2);
static float	magnitude_clone(t_tuple *t);
static t_tuple	*normalize_clone(t_tuple *t);
static void	ft_tuple_print_clone(t_tuple *t);
static t_tuple	*create_tuple_clone(float x, float y, float z, float w);

/*
	copy pasting bc I'm lazy
*/
static t_tuple *add_clone(t_tuple *t1, t_tuple *t2)
{
	t_tuple *t;

	if (!t1 || !t2)
		return (NULL);
	t = malloc(1 * sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->x = t1->x + t2->x;
	t->y = t1->y + t2->y;
	t->z = t1->z + t2->z;
	t->w = t1->w + t2->w;
	return (t);
}

/*
	copy pasting bc I'm lazy
*/
static float magnitude_clone(t_tuple *t)
{
	float res;

	if (!t)
		return (ERROR);
	res = 0.0;
	if (t->w)
		printf("Error: magnitude is only for vectors\n");
	res = (float)sqrt((double)t->x * (double)t->x
					+ (double)t->y * (double)t->y
					+ (double)t->z * (double)t->z
					+ (double)t->w * (double)t->w);
	return (res);
}

/*
	copy pasting bc I'm lazy
*/
static t_tuple *normalize_clone(t_tuple *t)
{
	t_tuple	*res;
	float	mag;

	if (!t)
		return (NULL);
	mag = magnitude_clone(t);
	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = t->x / mag;
	res->y = t->y / mag;
	res->z = t->z / mag;
	res->w = t->w / mag;
	return (res);
}

/*
	copy pasting bc I'm lazy
*/
static void	ft_tuple_print_clone(t_tuple *t)
{
	if (!t)
	{
		printf("%sError: tuple is NULL%s\n", RED, ENDCLR);
		return ;
	}
	printf("x: %.3f | y: %.3f | z: %.3f | w: %.1f %s\n",
			t->x, t->y, t->z, t->w,
			t->w == 0 ? "(VECTOR)" : t->w == 1 ? "(POINT)" : "(neither)");
}

/*
	copy pasting bc I'm lazy
*/
static t_tuple *create_tuple_clone(float x, float y, float z, float w)
{
	t_tuple *t;

	t = malloc(1 * sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->x = x;
	t->y = y;
	t->z = z;
	t->w = w;
	return (t);
}

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

static int	tick_clone(t_environment *env, t_projectile *proj)
{
	t_tuple	*position;
	t_tuple	*velocity;
	t_tuple	*temp;

	temp = add_clone(proj->velocity, env->gravity);
	if (!temp)
		return (ERROR);
	position = add_clone(proj->position, proj->velocity);
	velocity = add_clone(temp, env->wind);
	if (!position || !velocity)
		return (ERROR);
	proj->position = position;
	proj->velocity = velocity;
	free(temp);

	return (SUCCESS);
}

int	main(void)
{
	t_environment	*env;
	t_projectile	*proj;
	int				tick_count;

	env = malloc(1 * sizeof(t_environment));
	proj = malloc(1 * sizeof(t_projectile));
	if (!env || !proj)
		return (ERROR);
	tick_count = 0;
	proj->position = create_tuple_clone(0, 1, 0, POINT);
	proj->velocity = normalize_clone(create_tuple_clone(1, 1, 0, VECTOR));
	env->gravity = create_tuple_clone(0, -0.1, 0, VECTOR);
	env->wind = create_tuple_clone(-0.01, 0, 0, VECTOR);
	while (proj->position->y > 0)
	{
		if (tick_clone(env, proj) == ERROR)
			return (ERROR);
		ft_tuple_print_clone(proj->position);
		tick_count++;
	}
	printf("Projectile has landed after %d ticks at:\n", tick_count);
	ft_tuple_print_clone(proj->position);
	// free(proj->position);
	// free(proj->velocity);
	return (SUCCESS);
}
