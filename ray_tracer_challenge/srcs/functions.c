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

t_tuple *scale_tuple(t_tuple *t, float scalar)
{
    t_tuple *t1;

    t1 = malloc(1 * sizeof(t_tuple));
    if (!t1)
        return (NULL);
    t1->x = t->x * scalar;
    t1->y = t->y * scalar;
    t1->z = t->z * scalar;
    t1->w = t->w * scalar;
    return (t1);
}

