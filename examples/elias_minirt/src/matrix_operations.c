/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:14:29 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/23 11:21:25 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	matrix_are_equal(t_matrix *a, t_matrix *b)
{
	int	i;
	int	j;

	if (a->size != b->size)
		return (0);
	i = 0;
	while (i < a->size)
	{
		j = 0;
		while (j < a->size)
		{
			if (equal_float(a->m[i][j], b->m[i][j] == 0))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

float	*four_one_multiply(t_matrix *a, float *b, int delete)
{
	float	*result;
	int		i;

	i = 0;
	result = tuple(0, 0, 0, 0);
	if (!result)
		return (NULL);
	while (i < 4)
	{
		result[i] = dot_product(a->m[i], b);
		i++;
	}
	if (delete == 1)
	{
		free(b);
		b = NULL;
	}
	return (result);
}

t_matrix	*matrix_multiply(t_matrix *a, t_matrix *b, int delete)
{
	t_matrix	*matrix;
	int			i;
	int			j;

	matrix = create_matrix(a->size);
	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			matrix->m[i][j] = (a->m[i][0] * b->m[0][j])
				+ (a->m[i][1] * b->m[1][j])
				+ (a->m[i][2] * b->m[2][j]) + (a->m[i][3] * b->m[3][j]);
	}
	if (delete == 1)
	{
		clean_matrix(a, 4);
		clean_matrix(b, 4);
	}
	return (matrix);
}

t_matrix	*transpose(t_matrix *a)
{
	t_matrix	*trans;
	int			i;
	int			j;

	trans = create_matrix(a->size);
	if (!trans)
		return (NULL);
	i = -1;
	while (++i < a->size)
	{
		j = -1;
		while (++j < a->size)
			trans->m[i][j] = a->m[j][i];
	}
	return (trans);
}

float	cofactor(t_matrix *a, int i, int j)
{
	int		k;
	float	min;

	min = minor(a, i, j);
	k = i + j;
	if (k % 2 == 0)
		return (min);
	else
		return (-min);
}
