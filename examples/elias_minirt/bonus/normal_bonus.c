/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:14:21 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

static float	get_y_value(t_shape shape, float *object_p)
{
	float	y;

	y = 0;
	if (shape == CONE)
	{
		y = sqrt(object_p[0] * object_p[0] + object_p[2] * object_p[2]);
		if (object_p[1] > 0)
			y = -y;
	}
	return (y);
}

static float	*local_normal_at(t_shape shape, float *obj_p, t_object *object)
{
	float	dist;
	float	y;

	if (shape == PLANE)
		return (create_vector(0, 1, 0));
	else if (shape == SPHERE)
		return (create_vector(obj_p[0], obj_p[1], obj_p[2]));
	else if (shape == CYLINDER || shape == CONE)
	{
		dist = obj_p[0] * obj_p[0] + obj_p[2] * obj_p[2];
		if (dist < 1 && obj_p[1] >= object->cylindermax - 1e-6)
			return (create_vector(0, 1, 0));
		else if (dist < 1 && obj_p[1] <= object->cylindermin + 1e-6)
			return (create_vector(0, -1, 0));
		else
		{
			y = get_y_value(shape, obj_p);
			return (create_vector(obj_p[0], y, obj_p[2]));
		}
	}
	else
		return (NULL);
}

float	*normal_at(t_object *object, float *world_p)
{
	float		*object_p;
	float		*object_normal;
	float		*world_normal;
	t_matrix	*transposed;

	object_p = four_one_multiply(object->transform, world_p, 0);
	object_normal = local_normal_at(object->s, object_p, object);
	if (object_normal == NULL)
	{
		free(object_p);
		return (NULL);
	}
	transposed = transpose(object->transform);
	world_normal = four_one_multiply(transposed, object_normal, 1);
	world_normal[3] = 0;
	clean_matrix(transposed, transposed->size);
	free(object_p);
	object_p = normalize(world_normal, 1);
	return (object_p);
}
