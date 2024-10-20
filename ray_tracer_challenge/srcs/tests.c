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
    t_tuple *v2 = create_vector(3, 2, 1);

    t_tuple *r2 = subtract(p1, v1);

    ft_putstring("Subtract - isn't that cool!\n");
    ft_putstring("Subtracting two points\n");
    t_tuple *r1 = subtract(p1, p2);
    ft_tuple_print(r1);

    ft_putstring("Subtracting a vector from a point\n");
    ft_putstring("should be p -2, -4, -6\n");
    ft_tuple_print(r2);

    ft_putstring("Subtracting two vectors\n");
    t_tuple *r3 = subtract(v2, v1);
    ft_putstring("should be v -2, -4, -6\n");
    ft_tuple_print(r3);

    t_tuple *zero = create_vector(0, 0, 0);
    t_tuple *v3 = create_vector(1, -2, 3);
    ft_putstring("Subtracting a vector from the zero vector\n");
    ft_putstring("should be -1, 2, -3\n");
    t_tuple *r4 = subtract(zero, v3);
    ft_tuple_print(r4);

    ft_putstring("Negating a tuple\n");
    t_tuple *a1 = create_tuple(1, -2, 3, -4);
    t_tuple *r5 = negate_tuple(a1);
    ft_putstring("should be -1, 2, -3, 4\n");
    ft_tuple_print(r5);

    ft_putstring("Multiply a tuple by a scalar\n");
    t_tuple *r6 = scale_tuple(a1, 3.5);
    ft_tuple_print(a1);
    ft_putstring("should be 3.5, -7, 10.5, -14\n");
    ft_tuple_print(r6);

    free(p);
    free(v);
    free(a);
    free(p1);
    free(p2);
    free(v1);
    free(r1);   
    free(r2);

}