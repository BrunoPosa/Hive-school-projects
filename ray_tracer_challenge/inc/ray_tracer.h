#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 0.00001

// typedef enum    e_type{
//     VECTOR,
//     POINT,
// }               t_type;


typedef struct	s_tuple
{
    float x;
    float y;
    float z;
    // t_type w;
    float w;
}               t_tuple;

void	ft_putstring(char *s);
void    tests(void);
void	ft_tuple_print(t_tuple *t);
int     compare(t_tuple *t1, t_tuple *t2);
t_tuple    *create_point(float x, float y, float z);
t_tuple    *create_vector(float x, float y, float z);
t_tuple    *add(t_tuple *t1, t_tuple *t2);
t_tuple *subtract(t_tuple *t1, t_tuple *t2);
