#include "../inc/file_to_list.h"

/*
	returns number of differences between the two tuples;
	0 if identical, ERROR on errors.
*/
int diff(t_tuple *t1, t_tuple *t2)
{
	int diff_count = 0;

	if (!t1 || !t2)
		return (ERROR);
	if (fabs(t1->x - t2->x) > EPSILON)
	{
		printf("x is different\n");
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

/*
	returns a new tuple, or NULL on errors
*/
t_tuple *add(t_tuple *t1, t_tuple *t2)
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
	returns a new tuple or NULL on errors
*/
t_tuple *subtract(t_tuple *t1, t_tuple *t2)
{
	t_tuple *res;

	if (!t1 || !t2)
		return (NULL);
	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = t1->x - t2->x;
	res->y = t1->y - t2->y;
	res->z = t1->z - t2->z;
	res->w = t1->w - t2->w;
	return (res);
}

/*
	returns a new tuple or NULL on errors
*/
t_tuple *negate_tuple(t_tuple *t)
{
	t_tuple *res;

	if (!t)
		return (NULL);
	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = -t->x;
	res->y = -t->y;
	res->z = -t->z;
	res->w = -t->w;
	return (res);
}

/*
	returns a new tuple, or NULL on errors
*/
t_tuple *multiply_tuple(t_tuple *t, float multiplier)
{
	t_tuple *res;

	if (!t)
		return (NULL);
	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = t->x * multiplier;
	res->y = t->y * multiplier;
	res->z = t->z * multiplier;
	res->w = t->w * multiplier;
	return (res);
}

/*
	returns a new tuple, or NULL on errors
*/
t_tuple *divide_tuple(t_tuple *t, float divisor)
{
	t_tuple *res;

	if (!t || divisor == 0)
		return (NULL);
	res = malloc(1 * sizeof(t_tuple));
	if (!res)
		return (NULL);
	res->x = t->x / divisor;
	res->y = t->y / divisor;
	res->z = t->z / divisor;
	res->w = t->w / divisor;
	return (res);
}

/*
	returns the magnitude of the vector, or ERROR on errors
*/
float magnitude(t_tuple *t)
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
	returns a new vector (normalized input vector), or NULL on errors
*/
t_tuple *normalize(t_tuple *t)
{
	t_tuple	*res;
	float	mag;

	if (!t)
		return (NULL);
	mag = magnitude(t);
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
	returns the dot product of two vectors, or ERROR on errors
*/
float	dot(t_tuple *a, t_tuple *b)
{
	float result;

	if (!a || !b)
		return (ERROR);
	result = 0.0;
	if (a->w || b->w)
	{
		printf("Error: dot product is only for vectors\n");
		return(ERROR);
	}
	result = a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
	return (result);
}

/*
	returns a new vector (cross product of input vectors), or NULL on errors
*/
t_tuple *cross(t_tuple *a, t_tuple *b)
{
	t_tuple *t;

	if (!a || !b)
		return (NULL);
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
