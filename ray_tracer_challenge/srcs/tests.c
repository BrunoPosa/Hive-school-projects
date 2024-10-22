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
	//-------- print a tuple --------
	t_tuple	t;

	t.x = 1.0;
	t.y = 2.0;
	t.z = 3.0;
	t.w = 1;
	printf("tuple t:\n");
	ft_tuple_print(&t);
	ft_print_line('-');

	printf("%s-------- compare two tuples: --------%s\n", YELLOW, ENDCLR);
	float x = 1.1;
	float y = 2.2;
	float z = 3.3;
	t_tuple *p = create_tuple(x, y, z, POINT);
	printf("tuple p:\n");
	ft_tuple_print(p);
	t_tuple *v = create_tuple(x, y, z, VECTOR);
	printf("tuple v:\n");
	ft_tuple_print(v);

	if(compare(p, v) != 0)
		printf("%sCompare is KO%s\n", RED, ENDCLR);
	else
		printf("%sCompare is OK%s\n", GREEN, ENDCLR);
	ft_print_line('-');

	printf("%s-------- addition: --------%s\n  ", YELLOW, ENDCLR);
	ft_tuple_print(p);
	printf("+ ");
	ft_tuple_print(v);
	printf("= ");
	ft_tuple_print(add(p, v));
	ft_print_line('-');

	printf("%s-------- subtraction: --------%s\n", YELLOW, ENDCLR);
	t_tuple *p1 = create_tuple(3, 2, 1, POINT);
	t_tuple *p2 = create_tuple(5, 6, 7, POINT);
	t_tuple *v1 = create_tuple(5, 6, 7, VECTOR);
	t_tuple *v2 = create_tuple(3, 2, 1, VECTOR);
	printf("p1:");
	ft_tuple_print(p1);
	printf("p2:");
	ft_tuple_print(p2);
	printf("v1:");
	ft_tuple_print(v1);
	printf("v2:");
	ft_tuple_print(v2);

	printf("%sSubtracting two points%s\n  ", YELLOW, ENDCLR);
	ft_tuple_print(p1);
	printf("- ");
	ft_tuple_print(p2);
	printf("= ");
	ft_tuple_print(subtract(p1, p2));

	printf("%sSubtracting a vector from a point%s\n", YELLOW, ENDCLR);
	printf("should be p -2, -4, -6:\n");
	ft_tuple_print(subtract(p1, v1));

	printf("%sSubtracting two vectors%s\n", YELLOW, ENDCLR);
	printf("should be v -2, -4, -6:\n");
	ft_tuple_print(subtract(v2, v1));

	t_tuple *zero = create_tuple(0, 0, 0, VECTOR);
	t_tuple *v3 = create_tuple(1, -2, 3, VECTOR);
	printf("%sSubtracting a vector from the zero vector%s\n", YELLOW, ENDCLR);
	printf("should be -1, 2, -3\n");
	t_tuple *r4 = subtract(zero, v3);
	ft_tuple_print(r4);
	ft_print_line('-');

	//-------- Negating a tuple --------
	printf("%sNegating a tuple%s\n", YELLOW, ENDCLR);
	t_tuple *a1 = create_tuple(1, -2, 3, -4);
	printf("should be -1, 2, -3, 4\n");
	ft_tuple_print(negate_tuple(a1));
	ft_print_line('-');

	//-------- Multiply and divide --------
	printf("%sMultiply a tuple by a scalar%s\n", YELLOW, ENDCLR);
	ft_tuple_print(a1);
	printf("should be 3.5, -7, 10.5, -14\n");
	ft_tuple_print(multiply_tuple(a1, 3.5));

	printf("%sMultiply a tuple by a fraction%s\n", YELLOW, ENDCLR);
	t_tuple *r7 = multiply_tuple(a1, 0.5);
	ft_tuple_print(a1);
	printf("should be 0.5, -1, 1.5, -2\n");
	ft_tuple_print(r7);

	printf("%sDivide a tuple by a scalar%s\n", YELLOW, ENDCLR);
	t_tuple *r8 = divide_tuple(a1, 2);
	ft_tuple_print(a1);
	printf("should be 0.5, -1, 1.5, -2\n");
	ft_tuple_print(r8);
	ft_print_line('-');

	//-------- Magnitude and normalization --------
	printf("%s------- Magnitude and normalization -------%s\n", YELLOW, ENDCLR);
	printf("%sMagnitude of vector%s\n", YELLOW, ENDCLR);
	t_tuple *v4 = create_tuple(1, 0, 0, VECTOR);
	t_tuple *v5 = create_tuple(1, 2, 3, VECTOR);
	t_tuple *v6 = create_tuple(-1, -2, -3, VECTOR);
	printf("magnitude of v4 = %f\n", magnitude(v4));
	printf("magnitude of v5 = %f\n", magnitude(v5));
	printf("magnitude of v6 = %f\n", magnitude(v6));

	printf("Normalize vector\n");
	t_tuple *v7 = create_tuple(4, 0, 0, VECTOR);
	printf("Expected normalized values\n");
	ft_tuple_print(normalize(v5));
	ft_tuple_print(normalize(v7));

	printf("Dot product of two vectors\n");
	t_tuple *v8 = create_tuple(2, 3, 4, VECTOR);
	printf("Tuple a:\n");
	ft_tuple_print(v5);
	printf("Tuple b:\n");
	ft_tuple_print(v8);
	printf("Dot product:%f\n", dot(v5, v8));
	printf("Expected value: 20\n");

	printf("Cross product of two vectors\n");
	t_tuple *r15 = cross(v5, v8);
	t_tuple *r16 = cross(v8, v5);
	ft_tuple_print(r15);
	ft_tuple_print(r16);


	free(p);
	free(v);
	free(p1);
	free(p2);
	free(v1);
	free(r4);
	free(r7);
	free(a1);
	free(zero);
	free(v2);
	free(v3);


}