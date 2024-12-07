#include "../inc/file_to_list.h"

/*
	returns number of differences between the two vectors/points, 0 if identical
*/
int diff(t_vec a, t_vec b)
{
	int diff_count = 0;

	if (fabs(a.x - b.x) > EPSILON)
		diff_count++;
	if (fabs(a.y - b.y) > EPSILON)
		diff_count++;
	if (fabs(a.z - b.z) > EPSILON)     
		diff_count++;
	return (diff_count);
}

t_vec add(t_vec a, t_vec b)
{
	t_vec t;

	t.x = a.x + b.x;
	t.y = a.y + b.y;
	t.z = a.z + b.z;
	return (t);
}

t_vec subtract(t_vec a, t_vec b)
{
	t_vec res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

/*
	returns an inverted tuple
*/
t_vec negate_tuple(t_vec t)
{
	t_vec res;

	res.x = -t.x;
	res.y = -t.y;
	res.z = -t.z;
	return (res);
}

/*
	returns a tuple with each member multiplied
*/
t_vec multiply_tuple(t_vec t, float multiplier)
{
	t_vec res;

	res.x = t.x * multiplier;
	res.y = t.y * multiplier;
	res.z = t.z * multiplier;
	return (res);
}

/*
	returns a tuple with each member divided, or same tuple if divisor is 0
*/
t_vec divide_tuple(t_vec t, float divisor)
{
	t_vec res;

	if (divisor == 0)
		return (t);
	res.x = t.x / divisor;
	res.y = t.y / divisor;
	res.z = t.z / divisor;
	return (res);
}

float magnitude(t_vec t)
{
	return (sqrt(t.x * t.x + t.y * t.y + t.z * t.z));
}

/*
	returns the normalized input vector
*/
t_vec	normalize(t_vec t)
{
	t_vec	res;
	float	mag;

	mag = magnitude(t);
	res.x = t.x / mag;
	res.y = t.y / mag;
	res.z = t.z / mag;
	return (res);
}

/*
	returns dot product of two vectors
*/
float	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
	returns cross product of input vectors
*/
t_vec cross(t_vec a, t_vec b)
{
	t_vec t;

	t.x = a.y * b.z - a.z * b.y;
	t.y = a.z * b.x - a.x * b.z;
	t.z = a.x * b.y - a.y * b.x;
	return (t);
}
