/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:15:36 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

t_matrix	*create_populated_matrix(float *a, float *b, float *c, float *d)
{
	t_matrix	*matrix;
	int			n;

	if (a && b && c && d)
	{
		matrix = create_matrix(4);
		if (!matrix)
			return (NULL);
		n = -1;
		while (++n < 4)
			free(matrix->m[n]);
		matrix->m[0] = a;
		matrix->m[1] = b;
		matrix->m[2] = c;
		matrix->m[3] = d;
		return (matrix);
	}
	free(a);
	free(b);
	free(c);
	free(d);
	return (NULL);
}

t_matrix	*create_matrix(int n)
{
	t_matrix	*matrix;
	int			i;

	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->size = n;
	matrix->m = malloc(n * sizeof(float *));
	if (!matrix->m)
	{
		free(matrix);
		return (NULL);
	}
	i = -1;
	while (++i < 4)
	{
		matrix->m[i] = tuple(0, 0, 0, 0);
		if (matrix->m[i] == NULL)
		{
			clean_matrix(matrix, i);
			return (NULL);
		}
	}
	return (matrix);
}

void	clean_matrix(t_matrix *matrix, int n)
{
	int	j;

	j = 0;
	if (matrix)
	{
		while (j < n)
		{
			free(matrix->m[j]);
			j++;
		}
		free(matrix->m);
		free(matrix);
	}
	matrix = NULL;
}

t_matrix	*create_identity(int n)
{
	t_matrix	*matrix;
	int			i;

	matrix = create_matrix(n);
	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < 4)
		matrix->m[i][i] = 1;
	return (matrix);
}
