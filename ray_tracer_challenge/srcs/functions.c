#include "../inc/ray_tracer.h"

// returns the number of differences between the two tuples, 0 if they are the same
int diff(t_tuple *t1, t_tuple *t2)
{
	int diff_count = 0;

	if (fabs(t1->x - t2->x) > EPSILON)
	{    printf("x is different\n");
		diff_count++;
	}
	if (fabs(t1->y - t2->y) > EPSILON)
	{   
		printf("y is different\n");
		diff_count++;
	}
	if (fabs(t1->z - t2->z) > EPSILON)     
	{
		printf("z is different\n");
		diff_count++;
	}
	if ((t1->w - t2->w) > EPSILON)
	{
		printf("w is different\n");
		diff_count++;
	}
	return (diff_count);
}

t_tuple *add(t_tuple *t1, t_tuple *t2)
{
	t_tuple *t;

	t = malloc(1 * sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->x = t1->x + t2->x;
	t->y = t1->y + t2->y;
	t->z = t1->z + t2->z;
	t->w = t1->w + t2->w;
	return (t);
}   
t_tuple *subtract(t_tuple *t1, t_tuple *t2)
{
	t_tuple *res;

	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = t1->x - t2->x;
	res->y = t1->y - t2->y;
	res->z = t1->z - t2->z;
	res->w = t1->w - t2->w;
	return (res);
}
t_tuple *negate_tuple(t_tuple *t)
{
	t_tuple *res;

	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = -t->x;
	res->y = -t->y;
	res->z = -t->z;
	res->w = -t->w;
	return (res);
}

t_tuple *multiply_tuple(t_tuple *t, float multiplier)
{
	t_tuple *res;

	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = t->x * multiplier;
	res->y = t->y * multiplier;
	res->z = t->z * multiplier;
	res->w = t->w * multiplier;
	return (res);
}

t_tuple *divide_tuple(t_tuple *t, float divisor)
{
	t_tuple *res;

	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = t->x / divisor;
	res->y = t->y / divisor;
	res->z = t->z / divisor;
	res->w = t->w / divisor;
	return (res);
}

float magnitude(t_tuple *t)
{
	float res;

	res = 0.0;
	if (t->w)
		printf("Error: magnitude is only for vectors\n");
	res = (float)sqrt((double)t->x * (double)t->x
					+ (double)t->y * (double)t->y
					+ (double)t->z * (double)t->z
					+ (double)t->w * (double)t->w);
	return (res);
}

t_tuple *normalize(t_tuple *t)
{
	t_tuple	*res;
	float	mag;

	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	mag = magnitude(t);
	res->x = t->x / mag;
	res->y = t->y / mag;
	res->z = t->z / mag;
	res->w = t->w / mag;
	return (res);
}

float	dot(t_tuple *a, t_tuple *b)
{
	float result;

	result = 0.0;
	if (a->w || b->w)
		return(printf("Error: dot product is only for vectors\n"));
	result = a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
	return (result);
}

t_tuple *cross(t_tuple *a, t_tuple *b)
{
	t_tuple *t;

	t = malloc(1 * sizeof(t_tuple));
	if (!t)
		return (NULL);
	if (a->w || b->w)
	{
		printf("Error: cross product is only for vectors\n");
		free (t);
		return (NULL);
	}
	t->x = a->y * b->z - a->z * b->y;
	t->y = a->z * b->x - a->x * b->z;
	t->z = a->x * b->y - a->y * b->x;
	t->w = 0;
	return (t);
}
