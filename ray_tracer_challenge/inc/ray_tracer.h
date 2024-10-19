#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum e_type{
    VECTOR,
    POINT,
}           t_type; 


typedef struct	s_tuple
{
    float x;
    float y;
    float z;
    t_type w;
}               t_tuple;

void	ft_putstring(char *s);
void    tests(void);