/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:18:13 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 14:09:53 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_matrix	*create_translate(float a, float b, float c)
{
	t_matrix	*matrix;

	matrix = create_identity(4);
	if (!matrix)
		return (NULL);
	matrix->m[0][3] = a;
	matrix->m[1][3] = b;
	matrix->m[2][3] = c;
	return (matrix);
}

t_matrix	*create_scaling(float a, float b, float c)
{
	t_matrix	*matrix;

	matrix = create_identity(4);
	if (!matrix)
		return (NULL);
	matrix->m[0][0] = a;
	matrix->m[1][1] = b;
	matrix->m[2][2] = c;
	return (matrix);
}

t_matrix	*create_x_rotation(float a)
{
	t_matrix	*matrix;

	matrix = create_identity(4);
	if (!matrix)
		return (NULL);
	matrix->m[1][1] = cos(a);
	matrix->m[1][2] = -sin(a);
	matrix->m[2][1] = sin(a);
	matrix->m[2][2] = cos(a);
	return (matrix);
}

t_matrix	*create_y_rotation(float a)
{
	t_matrix	*matrix;

	matrix = create_identity(4);
	if (!matrix)
		return (NULL);
	matrix->m[0][0] = cos(a);
	matrix->m[0][2] = sin(a);
	matrix->m[2][0] = -sin(a);
	matrix->m[2][2] = cos(a);
	return (matrix);
}

t_matrix	*create_z_rotation(float a)
{
	t_matrix	*matrix;

	matrix = create_identity(4);
	if (!matrix)
		return (NULL);
	matrix->m[0][0] = cos(a);
	matrix->m[0][1] = -sin(a);
	matrix->m[1][0] = sin(a);
	matrix->m[1][1] = cos(a);
	return (matrix);
}
