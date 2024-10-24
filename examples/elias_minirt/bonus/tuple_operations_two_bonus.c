/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations_two_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:53:52 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

int	equal_float(float a, float b)
{
	if (fabs(a - b) < EPS)
		return (1);
	return (0);
}

float	magnitude(float *a)
{
	float	n;

	n = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	return (n);
}

float	*normalize(float *a, int delete)
{
	float	*p;
	float	mag;
	int		i;

	mag = magnitude(a);
	if (mag == 0)
	{
		printf("Magnitude is 0\n");
		return (NULL);
	}
	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		p[i] = a[i] / mag;
		i++;
	}
	if (delete == 1)
		free(a);
	return (p);
}

float	dot_product(float *a, float *b)
{
	float	p;
	int		i;

	p = 0;
	i = 0;
	while (i < 4)
	{
		p = p + (a[i] * b[i]);
		i++;
	}
	return (p);
}

float	*vector_cross_prod(float *a, float *b)
{
	float	*p;

	if (a[3] == 1 || b[3] == 1)
	{
		printf("Error: Cross product failed. Use vectors\n");
	}
	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	p[0] = (a[1] * b[2]) - (a[2] * b[1]);
	p[1] = (a[2] * b[0]) - (a[0] * b[2]);
	p[2] = (a[0] * b[1]) - (a[1] * b[0]);
	p[3] = 0;
	return (p);
}
