#include "../inc/ray_tracer.h"

t_tuple *create_tuple(float x, float y, float z, float w)
{
    t_tuple *t;
    t = malloc(1 * sizeof(t_tuple));
    
    t->x = x;
    t->y = y;
    t->z = z;
    t->w = w;
    return t;
}

t_tuple    *create_point(float x, float y, float z)
{
    t_tuple *t;

    t = malloc(1 * sizeof(t_tuple));
    t = create_tuple(x, y, z, 1);
    
    return t;
}

t_tuple    *create_vector(float x, float y, float z)
{
    t_tuple *t;

    t = malloc(1 * sizeof(t_tuple));
    t = create_tuple(x, y, z, 0);

    return t;
}