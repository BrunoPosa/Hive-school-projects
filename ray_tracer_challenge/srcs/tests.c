#include "../inc/ray_tracer.h"

void	tests(void)
{
    t_tuple	t;

    t.x = 1.0;
    t.y = 2.0;
    t.z = 3.0;
    t.w = VECTOR;
    ft_tuple_print(&t);
}