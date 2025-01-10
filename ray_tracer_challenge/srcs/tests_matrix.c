#include  "../inc/ray_tracer.h"

void	tests_matrix(void)
{
	//-------- Matrix --------

	print_y("Creating a 4x4 matrix\n");
	float *m1 = create_matrix_new(4, 4);
	matrix_assign_new(m1, 0, 0, 1, 4);
	matrix_assign_new(m1, 0, 1, 2, 4);
	matrix_assign_new(m1, 0, 2, 3, 4);
	matrix_assign_new(m1, 0, 3, 4, 4);
	matrix_assign_new(m1, 1, 0, 5.5, 4);
	matrix_assign_new(m1, 1, 2, 7.5, 4);
	matrix_assign_new(m1, 2, 2, 11, 4);
	matrix_assign_new(m1, 3, 0, 13.5, 4);
	matrix_assign_new(m1, 3, 2, 15.5, 4);
	ft_matrix_print_new(m1, 4, 4);

	print_y("Creating a 2x2 matrix\n");
	float *m2 = create_matrix_new(2, 2);
	matrix_assign_new(m2, 0, 0, -3, 2);
	matrix_assign_new(m2, 0, 1, 5, 2);
	matrix_assign_new(m2, 1, 0, 1, 2);
	matrix_assign_new(m2, 1, 1, -2, 2);
	ft_matrix_print_new(m2, 2, 2);

	print_y("Creating a 3x3 matrix\n");
	float *m3 = create_matrix_new(3, 3);
	matrix_assign_new(m3, 0, 0, -3, 3);
	matrix_assign_new(m3, 1, 1, -2, 3);
	matrix_assign_new(m3, 2, 2, 1, 3);
	ft_matrix_print_new(m3, 3, 3);


	print_y("Comparing matrices\n");
	float *m4 = create_matrix_new(2, 2);
	float *m5 = create_matrix_new(2, 2);
	matrix_fill_new(m4, 2, 2, 5.5);
	matrix_fill_new(m5, 2, 2, 5.5);
	matrix_assign_new(m5, 0, 0, 7, 2);
	ft_matrix_print_new(m4, 2, 2);
	print_y("to\n");
	ft_matrix_print_new(m5, 2, 2);
	printf("matrix 4 to matrix 5 = %d\n", matrix_compare_new(m4, m5, 2, 2));
	ft_print_line('-');

	print_y("Multiplying matrices\n");
	float	m6[16] = {1, 2, 3, 4,
					5, 6, 7, 8,
					9, 8, 7, 6,
					5, 4, 3, 2};
	ft_matrix_print_new(m6, 4, 4);
	print_y("x\n");
	float	m7[16] = {-2, 1, 2, 3,
					3, 2, 1, -1,
					4, 3, 6, 5,
					1, 2, 7, 8};
	ft_matrix_print_new(m7, 4, 4);
	print_y("=\n");
	float *m8 = matrix_multiply_new(m6, m7, 4, 4);
	ft_matrix_print_new(m8, 4, 4);
	ft_print_line('-');

	print_y("Multiplying a matrix by a tuple\n");
	float	m9[16] = {1, 2, 3, 4,
					2, 4, 4, 2,
					8, 6, 4, 1,
					0, 0, 0, 1};
	ft_matrix_print_new(m9, 4, 4);
	t_tuple *t = create_tuple(1, 2, 3, 1);
	print_y("x\n");
	ft_tuple_print(t);
	print_y("=\n");
	ft_tuple_print(matrix_tuple_multiply_new(m9, t));

	// print_y("Creating a 4x4 matrix\n");
	// float **matrix1 = matrix_create(4, 4);

	// matrix_assign(matrix1, 0, 0, 1);
	// matrix_assign(matrix1, 0, 1, 2);
	// matrix_assign(matrix1, 0, 2, 3);
	// matrix_assign(matrix1, 0, 3, 4);
	// matrix_assign(matrix1, 1, 0, 5.5);
	// matrix_assign(matrix1, 1, 2, 7.5);
	// matrix_assign(matrix1, 2, 2, 11);
	// matrix_assign(matrix1, 3, 0, 13.5);
	// matrix_assign(matrix1, 3, 2, 15.5);

	// matrix_print(matrix1, 4, 4);
	// ft_print_line('-');

	// print_y("Creating a 2x2 matrix\n");
	// float **matrix2 = matrix_create(2, 2);
	// matrix_assign(matrix2, 0, 0, -3);
	// matrix_assign(matrix2, 0, 1, 5);
	// matrix_assign(matrix2, 1, 0, 1);
	// matrix_assign(matrix2, 1, 1, -2);

	// matrix_print(matrix2, 2, 2);
	// ft_print_line('-');

	// print_y("Creating a 3x3 matrix\n");
	// float **matrix3 = matrix_create(3, 3);
	// matrix_assign(matrix3, 0, 0, -3);
	// matrix_assign(matrix3, 1, 1, -7);
	// matrix_assign(matrix3, 2, 2, 1);

	// matrix_print(matrix3, 3, 3);
	// ft_print_line('-');
	// float **matrix4 = matrix_create(4, 4);
	// float **matrix5 = matrix_create(4, 4);
	// float **matrix6 = matrix_create(4, 4);
	// matrix_fill(matrix4, 4, 4, 5);
	// matrix_fill(matrix5, 4, 4, 5);
	// matrix_fill(matrix6, 4, 4, 6);
	// printf("matrix4 4 to matix 5 = %d\n", matrix_compare(matrix4, matrix5, 4, 4));
	// printf("matrix4 5 to matix 6 = %d\n", matrix_compare(matrix4, matrix6, 4, 4));
	
	// ft_print_line('-');


	// print_y("Multiplying matrices\n");
	// float **matrix7 = matrix_create(4, 4);
	// matrix_assign(matrix7, 0, 0, 1);
	// matrix_assign(matrix7, 0, 1, 2);
	// matrix_assign(matrix7, 0, 2, 3);
	// matrix_assign(matrix7, 0, 3, 4);
	// matrix_assign(matrix7, 1, 0, 5);
	// matrix_assign(matrix7, 1, 1, 6);
	// matrix_assign(matrix7, 1, 2, 7);
	// matrix_assign(matrix7, 1, 3, 8);
	// matrix_assign(matrix7, 2, 0, 9);
	// matrix_assign(matrix7, 2, 1, 8);
	// matrix_assign(matrix7, 2, 2, 7);
	// matrix_assign(matrix7, 2, 3, 6);
	// matrix_assign(matrix7, 3, 0, 5);
	// matrix_assign(matrix7, 3, 1, 4);
	// matrix_assign(matrix7, 3, 2, 3);
	// matrix_assign(matrix7, 3, 3, 2);
	// print_g("Matrix 7\n");
	// matrix_print(matrix7, 4, 4);
	// ft_print_line('-');
	// float **matrix8 = matrix_create(4, 4);
	// matrix_assign(matrix8, 0, 0, -2);
	// matrix_assign(matrix8, 0, 1, 1);
	// matrix_assign(matrix8, 0, 2, 2);
	// matrix_assign(matrix8, 0, 3, 3);
	// matrix_assign(matrix8, 1, 0, 3);
	// matrix_assign(matrix8, 1, 1, 2);
	// matrix_assign(matrix8, 1, 2, 1);
	// matrix_assign(matrix8, 1, 3, -1);
	// matrix_assign(matrix8, 2, 0, 4);
	// matrix_assign(matrix8, 2, 1, 3);
	// matrix_assign(matrix8, 2, 2, 6);
	// matrix_assign(matrix8, 2, 3, 5);
	// matrix_assign(matrix8, 3, 0, 1);
	// matrix_assign(matrix8, 3, 1, 2);
	// matrix_assign(matrix8, 3, 2, 7);
	// matrix_assign(matrix8, 3, 3, 8);
	// print_g("Matrix 8\n");
	// matrix_print(matrix8, 4, 4);
	// ft_print_line('-');
	// float **matrix9 = matrix_multiply(matrix7, matrix8, 4, 4);
	// print_g("Matrix 9 - multiplication of matrix 7 and 8\n");
	// matrix_print(matrix9, 4, 4);
	// ft_print_line('-');

	// print_y("OMG let's try a smaller Multiplying matrices\n");

	// float **matrix10 = matrix_create(2, 2);

	// matrix_assign(matrix10, 0, 0, 1);
	// matrix_assign(matrix10, 0, 1, 2);
	// matrix_assign(matrix10, 1, 0, 5);
	// matrix_assign(matrix10, 1, 1, 6);

	// print_g("Matrix 10\n");
	// matrix_print(matrix10, 2, 2);
	// ft_print_line('-');

	// float **matrix11 = matrix_create(2, 2);
	// matrix_fill(matrix11, 2, 2, 2);
	// print_g("Matrix 11\n");
	// matrix_print(matrix11, 2, 2);
	// ft_print_line('-');

	// float **matrix12 = matrix_multiply(matrix10, matrix11, 2, 2);
	// print_g("Matrix 12 - multiplication of matrix 10 and 11\n");
	// matrix_print(matrix12, 2, 2);
	// ft_print_line('-');
//---
// Matrix multiplied by a tuple

	// print_y("Multiplying a matrix by a tuple\n");
	// float **matrix13 = matrix_create(4, 4);
	// matrix_assign(matrix13, 0, 0, 1);
	// matrix_assign(matrix13, 0, 1, 2);
	// matrix_assign(matrix13, 0, 2, 3);
	// matrix_assign(matrix13, 0, 3, 4);
	// matrix_assign(matrix13, 1, 0, 2);
	// matrix_assign(matrix13, 1, 1, 4);
	// matrix_assign(matrix13, 1, 2, 4);
	// matrix_assign(matrix13, 1, 3, 2);
	// matrix_assign(matrix13, 2, 0, 8);
	// matrix_assign(matrix13, 2, 1, 6);
	// matrix_assign(matrix13, 2, 2, 4);
	// matrix_assign(matrix13, 2, 3, 1);
	// matrix_assign(matrix13, 3, 0, 0);
	// matrix_assign(matrix13, 3, 1, 0);
	// matrix_assign(matrix13, 3, 2, 0);
	// matrix_assign(matrix13, 3, 3, 1);
	// print_g("Matrix 13\n");
	// matrix_print(matrix13, 4, 4);
	// t_tuple *t = create_tuple(1, 2, 3, 1);
	// print_g("Tuple\n");
	// ft_tuple_print(t);
	// ft_print_line('-');
	// float **t2 = matrix_tuple_multiply(matrix13, t, 4, 4);
	// print_g("Tuple after multiplication\n");
	// ft_tuple_print(t2);
	// ft_print_line('-');


	
	// print_y("Creating a matrix\n");
	// t_matrix *m = create_matrix(4, 4);
	// printf("matrix is 4x4\n");
	// printf("m->rows = %zu, m->cols = %zu\n", m->rows, m->cols);
	// ft_print_line('-');

	// print_y("Creating a matrix\n");
	// t_matrix *m = create_matrix(4, 4);
	// printf("matrix is 4x4\n");
	// printf("m->rows = %zu, m->cols = %zu\n", m->rows, m->cols);
	// ft_print_line('-');

	// print_y("Creating a matrix\n");
	// t_matrix *m = create_matrix(4, 4);
	// printf("matrix is 4x4\n");
	// printf("m->rows = %zu, m->cols = %zu\n", m->rows, m->cols);
	// ft_print_line('-');

	// print_y("Creating a matrix\n");
	// t_matrix *m = create_matrix(4, 4);
	// printf("matrix is 4x4\n");
	// printf("m->rows = %zu, m->cols = %zu\n", m->rows, m->cols);
	// ft_print_line('-');

	// print_y("Creating a matrix\n");
	// t_matrix *m = create_matrix(4, 4);
	// printf("matrix is 4x4\n");
	// printf("m->rows = %zu, m->cols = %zu\n", m->rows, m->cols);
	// ft_print_line('-');

	// print_y("Creating a matrix\n");
	// t_matrix *m = create_matrix(4, 4);
	// printf("matrix is 4x4\n");
	// printf("m->rows = %zu, m->cols = %zu\n", m->rows, m->cols);
	// ft_print_line('-');

	// print_y("Creating a matrix\n");
	// t_matrix *m = create_matrix(4, 4);
	// printf("matrix is 4x4\n");
	// printf("m->rows = %zu, m->cols = %zu\n", m->rows, m->cols); 
	// ft_print_line('-');

}