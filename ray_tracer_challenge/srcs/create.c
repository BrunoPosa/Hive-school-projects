#include "../inc/ray_tracer.h"

t_tuple    *create_point(float x, float y, float z)
{
    t_tuple *t;
    t = malloc(1 * sizeof(t_tuple));
    
    t->x = x;
    t->y = y;
    t->z = z;
    t->w = POINT;
    return t;
}

t_tuple    *create_vector(float x, float y, float z)
{
    t_tuple *t;
    t = malloc(1 * sizeof(t_tuple));
    
    t->x = x;
    t->y = y;
    t->z = z;
    t->w = VECTOR;
    return t;
}