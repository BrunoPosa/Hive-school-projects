#include <unistd.h>
#include <math.h>

typedef enum e_type{
    VECTOR,
    POINT,
}           t_type; 


typedef struct	s_tuple
{
    double x;
    double y;
    double z;
    t_type w;
}               t_tuple;

void	ft_putstring(char *s);
void    tests(void);