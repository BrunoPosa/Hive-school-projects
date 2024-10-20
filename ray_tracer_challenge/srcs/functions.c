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

