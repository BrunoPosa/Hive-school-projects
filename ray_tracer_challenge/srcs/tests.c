#include "../inc/ray_tracer.h"

/*
test_compare(void)
{
    t_tuple	t1;
    t_tuple	t2;

    t1.x = 1.0;
    t1.y = 2.0;
    t1.z = 3.0;
    t1.w = VECTOR;

    t2.x = 1.0;
    t2.y = 2.0;
    t2.z = 3.0;
    t2.w = VECTOR;

    printf("Test 1: ");
    if (compare(&t1, &t2) == 0)
        printf("OK\n");
    else
        printf("KO\n");

    t2.x = 1.0;
    t2.y = 2.0;
    t2.z = 3.0;
    t2.w = POINT;

    printf("Test 2: ");
    if (compare(&t1, &t2) == 1)
        printf("OK\n");
    else
        printf("KO\n");

    t2.x = 1.0;
    t2.y = 2.0;
    t2.z = 3.0;
    t2.w = VECTOR;

    t2.x = 1.0;
    t2.y = 2.0;
    t2.z = 3.1;
    t2.w = VECTOR;

    printf("Test 3: ");
    if (compare(&t1, &t2) == 1)
        printf("OK\n");
    else
        printf("KO\n");

    t2.x = 1.0;
    t2.y = 2.0;
    t2.z = 3.0;
    t2.w = VECTOR;

    t2.x = 1.0;
    t2.y = 2.1;
    t2.z = 3.0;
    t2.w = VECTOR;

    printf("Test 4: ");
    if (compare(&t1, &t2) == 1)
        printf("OK\n");
    else
        printf("KO\n");

    t2.x = 1.0;
    t2.y = 2.0;
    t2.z = 3.0;
    t2.w = VECTOR;

    t2.x = 1.1;
    t2.y = 2.0;
    t2.z = 3.0;
    t2  .w = VECTOR;  
*/
void	tests(void)
{
    t_tuple	t;

    t.x = 1.0;
    t.y = 2.0;
    t.z = 3.0;
    t.w = VECTOR;
    ft_tuple_print(&t);

    float x = 1.1;
    float y = 2.2;
    float z = 3.3;

    t_tuple *p = create_point(x, y, z);

    ft_tuple_print(p);

    t_tuple *v = create_vector(x, y, z);

    ft_tuple_print(v);

    compare(p, v);

    free(p);
    free(v);


}