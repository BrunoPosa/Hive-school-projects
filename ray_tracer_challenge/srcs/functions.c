#include "../inc/ray_tracer.h"

// returns the number of differences between the two tuples
int compare(t_tuple *t1, t_tuple *t2)
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
	if ((t1->w - t2->w) != 0)
	{
		printf("w is different\n");
		diff_count++;
	}
	return diff_count;
}

t_tuple *add(t_tuple *t1, t_tuple *t2)
{
	t_tuple *t;
	t = malloc(1 * sizeof(t_tuple));
	
	t->x = t1->x + t2->x;
	t->y = t1->y + t2->y;
	t->z = t1->z + t2->z;
	t->w = t1->w + t2->w;
	return t;
}   
t_tuple *subtract(t_tuple *t1, t_tuple *t2)
{
	t_tuple *t;
	t = malloc(1 * sizeof(t_tuple));
	
	t->x = t1->x - t2->x;
	t->y = t1->y - t2->y;
	t->z = t1->z - t2->z;
	t->w = t1->w - t2->w;
	return t;
}
t_tuple *negate_tuple(t_tuple *t)
{
	t_tuple *t1;
	t1 = malloc(1 * sizeof(t_tuple));
	
	t1->x = -t->x;
	t1->y = -t->y;
	t1->z = -t->z;
	t1->w = -t->w;
	return t1;
}

t_tuple *multiply_tuple(t_tuple *t, float multiplier)
{
	t_tuple *t1;

	t1 = malloc(1 * sizeof(t_tuple));
	if (!t1)
		return (NULL);
	t1->x = t->x * multiplier;
	t1->y = t->y * multiplier;
	t1->z = t->z * multiplier;
	t1->w = t->w * multiplier;
	return (t1);
}

t_tuple *divide_tuple(t_tuple *t, float divisor)
{
	t_tuple *t1;

	t1 = malloc(1 * sizeof(t_tuple));
	if (!t1)
		return (NULL);
	t1->x = t->x / divisor;
	t1->y = t->y / divisor;
	t1->z = t->z / divisor;
	t1->w = t->w / divisor;
	return (t1);
}

float magnitude(t_tuple *t)
{
	float result;

	result = 0.0;
	if (t->w)
	{
		printf("Error: magnitude is only for vectors\n");
		return(-1);
	}
	result = (float)sqrt((double)t->x * (double)t->x
						+ (double)t->y * (double)t->y
						+ (double)t->z * (double)t->z
						+ (double)t->w * (double)t->w);
	return (result);
}

t_tuple *normalize(t_tuple *t)
{
	t_tuple	*t1;
	float	mag;

	t1 = malloc(1 * sizeof(t_tuple));
	if (!t1)
		return (NULL);
	mag = magnitude(t);
	t1->x = t->x / mag;
	t1->y = t->y / mag;
	t1->z = t->z / mag;
	t1->w = t->w / mag;
	return (t1);
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