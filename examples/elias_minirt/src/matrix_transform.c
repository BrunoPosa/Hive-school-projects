/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:06:52 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 14:09:22 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static t_matrix	*rodrd_rformula(float cos_theta, float sin_theta, float *axis)
{
	t_matrix	*rotation;
	float		one_minus_cos;			

	rotation = create_identity(4);
	one_minus_cos = 1.0f - cos_theta;
	rotation->m[0][0] = cos_theta + one_minus_cos * axis[0] * axis[0];
	rotation->m[0][1] = one_minus_cos * axis[0] * axis[1] - axis[2] * sin_theta;
	rotation->m[0][2] = one_minus_cos * axis[0] * axis[2] + axis[1] * sin_theta;
	rotation->m[0][3] = 0.0f;
	rotation->m[1][0] = one_minus_cos * axis[1] * axis[0] + axis[2] * sin_theta;
	rotation->m[1][1] = cos_theta + one_minus_cos * axis[1] * axis[1];
	rotation->m[1][2] = one_minus_cos * axis[1] * axis[2] - axis[0] * sin_theta;
	rotation->m[1][3] = 0.0f;
	rotation->m[2][0] = one_minus_cos * axis[2] * axis[0] - axis[1] * sin_theta;
	rotation->m[2][1] = one_minus_cos * axis[2] * axis[1] + axis[0] * sin_theta;
	rotation->m[2][2] = cos_theta + one_minus_cos * axis[2] * axis[2];
	rotation->m[2][3] = 0.0f;
	rotation->m[3][0] = 0.0f;
	rotation->m[3][1] = 0.0f;
	rotation->m[3][2] = 0.0f;
	rotation->m[3][3] = 1.0f;
	return (rotation);
}

static t_matrix	*create_axis_rotation(float *axis, float angle)
{
	t_matrix	*rotation;
	float		cos_theta;
	float		sin_theta;
	float		magnitude;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	magnitude = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
	axis[0] /= magnitude;
	axis[1] /= magnitude;
	axis[2] /= magnitude;
	rotation = rodrd_rformula(cos_theta, sin_theta, axis);
	return (rotation);
}

static t_matrix	*create_rotation_plane(t_object *o)
{
	t_matrix	*rotation;
	float		angle;
	float		dot;
	float		*up;
	float		*rotation_axis;

	up = create_vector(0, 1, 0);
	dot = dot_product(o->normv, up);
	angle = acos(dot);
	rotation_axis = vector_cross_prod(o->normv, up);
	if (magnitude(rotation_axis) > 1e-6)
		rotation = create_axis_rotation(rotation_axis, angle);
	else
		rotation = create_identity(4);
	free(rotation_axis);
	free(up);
	return (rotation);
}

static t_matrix	*create_rotation_cylinder(t_object *o)
{
	float		theta_x;
	float		theta_y;
	t_matrix	*rotation;
	t_matrix	*x;
	t_matrix	*y;

	theta_x = atan2(o->normv[2], o->normv[0]);
	theta_y = acos(o->normv[1]);
	x = create_x_rotation(theta_x);
	y = create_y_rotation(theta_y);
	rotation = matrix_multiply(x, y, 1);
	return (rotation);
}

t_matrix	*create_transform(t_matrix *transform, t_object *o)
{
	t_matrix	*temp;
	t_matrix	*scale;
	t_matrix	*rotation;

	temp = create_translate(o->coord[0], o->coord[1], o->coord[2]);
	if (o->s == SPHERE)
		scale = create_scaling(o->diameter / 2,
				o->diameter / 2, o->diameter / 2);
	else if (o->s == CYLINDER || o->s == CONE)
		scale = create_scaling(o->diameter / 2, o->height, o->diameter / 2);
	else
		scale = create_identity(4);
	if (o->s == PLANE)
		rotation = create_rotation_plane(o);
	else if (o->s == CYLINDER || o->s == CONE)
		rotation = create_rotation_cylinder(o);
	else
		rotation = create_identity(4);
	temp = matrix_multiply(temp, rotation, 1);
	clean_matrix(transform, 4);
	temp = matrix_multiply(temp, scale, 1);
	transform = inverse_matrix(temp);
	clean_matrix(temp, 4);
	return (transform);
}
