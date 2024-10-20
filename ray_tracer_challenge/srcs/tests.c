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
    t.w = 1;
    ft_tuple_print(&t);

    float x = 1.1;
    float y = 2.2;
    float z = 3.3;

    t_tuple *p = create_point(x, y, z);

    ft_tuple_print(p);

    t_tuple *v = create_vector(x, y, z);

    ft_tuple_print(v);

    if(compare(p, v) != 0)
        ft_putstring("Compare is KO\n");
    else
        ft_putstring("Compare is OK\n");

    t_tuple *a = add(p, v);

    ft_tuple_print(a);

    t_tuple *p1 = create_point(3, 2, 1);
    t_tuple *p2 = create_point(5, 6, 7);
    t_tuple *v1 = create_vector(5, 6, 7);
    t_tuple *r1 = subtract(p1, p2);
    t_tuple *r2 = subtract(p1, v1);

    ft_putstring("Subtract - isn't that cool!\n");
    ft_tuple_print(v1);

    ft_putstring("should be p -2, -4, -6\n");
    ft_tuple_print(r2);

    free(p);
    free(v);
    free(a);
    free(p1);
    free(p2);
    free(v1);
    free(r1);   
    free(r2);

}