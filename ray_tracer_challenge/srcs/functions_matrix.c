#include "../inc/ray_tracer.h"

float **matrix_create(int x, int y)
{
	float **matrix;
	int i;

	matrix = malloc(sizeof(float *) * y);
	if (!matrix)
		return NULL;
	i = 0;
	while (i < y)
	{
		matrix[i] = malloc(sizeof(float) * x);
		if (!matrix[i])
			return NULL;
		i++;
	}
	return matrix;
}

float	*create_matrix_new(int cols, int rows)
{
	float *matrix;
	int i;

	matrix = malloc(sizeof(float) * cols * rows);
	if (!matrix)
		return NULL;
	i = 0;
	//use bzero/memset from libft instead of this loop
	while (i < cols * rows)
	{
		matrix[i] = 0;
		i++;
	}
	return (matrix);
}

void matrix_assign(float **matrix, int x, int y, float f)
{
	matrix[x][y] = f;
}

/* 
	rows and cols start at zero
*/
void	matrix_assign_new(float *matrix, int row, int col, float value, unsigned int matrixsize)
{
	matrix[row * matrixsize + col] = value;
}

void matrix_print(float **matrix, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%f ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// 1 is equal, 0 is not equal
int matrix_compare(float **matrix1, float **matrix2, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (matrix1[i][j] != matrix2[i][j])
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

/*
	1 is equal, 0 is not equal
*/
int	matrix_compare_new(float *matrix1, float *matrix2, unsigned int width, unsigned int height)
{
	unsigned int i;

	i = 0;
	while (i < width * height)
	{
		if (matrix1[i] != matrix2[i])
			return 0;
		i++;
	}
	return 1;
}

void matrix_fill(float **matrix, int x, int y, float f)
{
	int i;
	int j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			matrix[i][j] = f;
			j++;
		}
		i++;
	}
}

void	matrix_fill_new(float *matrix, unsigned int width, unsigned int height, float value)
{
	unsigned int i;

	i = 0;
	while (i < width * height)
	{
		matrix[i] = value;
		i++;
	}
}

float **matrix_multiply(float **matrix1, float **matrix2, int x, int y)
{
	float **matrix;
	int i;
	int j;
	int k;

	matrix = matrix_create(x, y);
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			matrix[i][j] = 0;
			k = 0;
			while (k < x)
			{
				matrix[i][j] += matrix1[i][k] * matrix2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return matrix;
}

float	*matrix_multiply_new(float *matrix1, float *matrix2, int width, int height)
{
	float *matrix;
	int i;
	int j;
	int k;

	matrix = create_matrix_new(width, height);
	if (!matrix)
		return NULL;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			k = -1;
			while (++k < width)
				matrix[i * width + j] += matrix1[i * width + k] * matrix2[k * width + j];
		}
	}
	return (matrix);
}

float **matric_tuple_multiply(float **matrix, t_tuple *t, int x, int y)
{
	float **r;
	int i;
	int j;

	r = matrix_create(x, y);
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			r[i][j] = matrix[i][j] * t->x + matrix[i][j + 1]
									* t->y + matrix[i][j + 2]
									* t->z + matrix[i][j + 3]
									* t->w;
			j++;
		}
		i++;
	}
	return r;
}

t_tuple	*matrix_tuple_multiply_new(float *matrix, t_tuple *t)
{
	t_tuple *result;

	if (!matrix || !t)
		return NULL;
	result = create_tuple(0, 0, 0, 0);
	if (!result)
		return NULL;
	result->x = matrix[0] * t->x + matrix[1] * t->y + matrix[2] * t->z + matrix[3] * t->w;
    result->y = matrix[4] * t->x + matrix[5] * t->y + matrix[6] * t->z + matrix[7] * t->w;
    result->z = matrix[8] * t->x + matrix[9] * t->y + matrix[10] * t->z + matrix[11] * t->w;
    result->w = matrix[12] * t->x + matrix[13] * t->y + matrix[14] * t->z + matrix[15] * t->w;
	return (result);
}

// t_tuple *matrix_tuple_multiply(float **matrix, t_tuple *t, int x, int y)
// {
//     t_tuple *result = (t_tuple *)malloc(sizeof(t_tuple));
	
//     for (int i = 0; i < y; i++)
//     {
//         result->x += matrix[i][0] * t->x + matrix[i][1] * t->y + matrix[i][2] * t->z + matrix[i][3] * t->w;
//         result->y += matrix[i + y][0] * t->x + matrix[i + y][1] * t->y + matrix[i + y][2] * t->z + matrix[i + y][3] * t->w;
//         result->z += matrix[i + 2 * y][0] * t->x + matrix[i + 2 * y][1] * t->y + matrix[i + 2 * y][2] * t->z + matrix[i + 2 * y][3] * t->w;
//         result->w += matrix[i + 3 * y][0] * t->x + matrix[i + 3 * y][1] * t->y + matrix[i + 3 * y][2] * t->z + matrix[i + 3 * y][3] * t->w;
//     }

//     return result;
// }