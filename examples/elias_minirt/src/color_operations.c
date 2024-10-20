/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:19:29 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 12:20:12 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	*color(float a, float b, float c)
{
	float	*color;

	color = malloc(3 * sizeof(float));
	if (!color)
		return (NULL);
	color[0] = a;
	color[1] = b;
	color[2] = c;
	return (color);
}

float	*hadamard(float *a, float *b)
{
	float	*result;

	result = color(0, 0, 0);
	if (!result)
		return (NULL);
	result[0] = a[0] * b[0];
	result[1] = a[1] * b[1];
	result[2] = a[2] * b[2];
	return (result);
}

float	*multiply_color(float *a, float b, int delete)
{
	float	*result;

	result = color(0, 0, 0);
	if (!result)
		return (NULL);
	result[0] = a[0] * b;
	result[1] = a[1] * b;
	result[2] = a[2] * b;
	if (delete == 1)
		free(a);
	return (result);
}

float	*add_colors(float *a, float *b, float *c)
{
	float	*result;

	result = color(0, 0, 0);
	if (!result)
		return (NULL);
	result[0] = a[0] + b[0] + c[0];
	result[1] = a[1] + b[1] + c[1];
	result[2] = a[2] + b[2] + c[2];
	free(a);
	free(b);
	free(c);
	return (result);
}

float	*add_two_colors(float *a, float *b)
{
	float	*result;

	result = color(0, 0, 0);
	if (!result)
		return (NULL);
	result[0] = a[0] + b[0];
	result[1] = a[1] + b[1];
	result[2] = a[2] + b[2];
	free(a);
	free(b);
	return (result);
}
