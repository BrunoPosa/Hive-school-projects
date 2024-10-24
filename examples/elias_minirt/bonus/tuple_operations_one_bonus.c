/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations_one_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:22:27 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

float	*tuple_add(float *a, float *b)
{
	float	*p;
	int		i;

	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		p[i] = a[i] + b[i];
		i++;
	}
	if (p[3] == 2)
		printf("Error: Adding two points. Unexpected result\n");
	return (p);
}

float	*tuple_subs(float *a, float *b)
{
	float	*p;
	int		i;

	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		p[i] = a[i] - b[i];
		i++;
	}
	if (p[3] < 0)
	{
		printf("Error: Substracting wrong parameters. Unexpected result\n");
		exit(1);
	}
	return (p);
}

float	*negate_vector(float *a)
{
	float	*p;
	float	*neg;

	p = tuple(0, 0, 0, 0);
	neg = tuple_subs(p, a);
	free(p);
	return (neg);
}

float	*scalar_multi_tuple(float *a, float n)
{
	float	*p;
	int		i;

	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		p[i] = a[i] * n;
		i++;
	}
	return (p);
}

float	*scalar_div_tuple(float *a, float n)
{
	float	*p;
	int		i;

	p = malloc(4 * sizeof(float));
	if (!p)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		p[i] = a[i] / n;
		i++;
	}
	return (p);
}
