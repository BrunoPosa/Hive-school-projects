#include "../inc/file_to_list.h"

/*
	allocates, fills and returns a new tuple, or NULL on errors.
	pass in VECTOR or POINT macro as 'w' parameter to specify the type of tuple.
*/
t_vec create_vec(float x, float y, float z)
{
	t_vec t;

	t.x = x;
	t.y = y;
	t.z = z;
	return (t);
}

// t_tuple *create_point(float x, float y, float z)
// {
// 	return (create_tuple(x, y, z, POINT));
// }

// t_tuple *create_vector(float x, float y, float z)
// {
// 	return (create_tuple(x, y, z, VECTOR));
// }


t_colour	*create_colour(float r, float g, float b)
{
	t_colour *c;

	c = NULL;
	// if (r == 0)
	// 	r = EPSILON;
	// if (g == 0)
	// 	g = EPSILON;
	// if (b == 0)
	// 	b = EPSILON;
	c = malloc(1 * sizeof(t_colour));
	if (!c)
		return (NULL);
	c->r = r;
	c->g = g;
	c->b = b;
	return (c);
}
