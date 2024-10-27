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

void matrix_assign(float **matrix, int x, int y, float f)
{
    matrix[x][y] = f;
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
t_tuple *matrix_tuple_multiply(float **matrix, t_tuple *t, int x, int y)
{
    t_tuple *result = (t_tuple *)malloc(sizeof(t_tuple));
    
    for (int i = 0; i < y; i++)
    {
        result->x += matrix[i][0] * t->x + matrix[i][1] * t->y + matrix[i][2] * t->z + matrix[i][3] * t->w;
        result->y += matrix[i + y][0] * t->x + matrix[i + y][1] * t->y + matrix[i + y][2] * t->z + matrix[i + y][3] * t->w;
        result->z += matrix[i + 2 * y][0] * t->x + matrix[i + 2 * y][1] * t->y + matrix[i + 2 * y][2] * t->z + matrix[i + 2 * y][3] * t->w;
        result->w += matrix[i + 3 * y][0] * t->x + matrix[i + 3 * y][1] * t->y + matrix[i + 3 * y][2] * t->z + matrix[i + 3 * y][3] * t->w;
    }

    return result;
}