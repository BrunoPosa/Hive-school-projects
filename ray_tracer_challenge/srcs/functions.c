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
#include <stdio.h>
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

