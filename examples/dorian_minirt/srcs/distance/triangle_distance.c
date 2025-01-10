/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:42:44 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/25 13:07:20 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

#define U 0
#define V 1
#define PVEC 0
#define TVEC 1
#define QVEC 2

float	dist_triangle(const t_ray *ray, t_object *obj)
{
	float	dist;
	float	det;
	float	inv_det;
	t_vec3	bary_vec[3];
	float	bary_weights[2];

	bary_vec[PVEC] = vec3_cross(ray->direction, obj->triangle.edges[1]);
	det = vec3_dot(obj->triangle.edges[0], bary_vec[PVEC]);
	if (fabs(det) < EPSILON)
		return (FLT_MAX);
	inv_det = 1.0 / det;
	bary_vec[TVEC] = vec3_sub(ray->origin, obj->triangle.tri_point[0]);
	bary_weights[U] = vec3_dot(bary_vec[TVEC], bary_vec[PVEC]) * inv_det;
	if (bary_weights[U] < 0.0 || bary_weights[U] > 1.0)
		return (FLT_MAX);
	bary_vec[QVEC] = vec3_cross(bary_vec[TVEC], obj->triangle.edges[0]);
	bary_weights[V] = vec3_dot(ray->direction, bary_vec[QVEC]) * inv_det;
	if (bary_weights[V] < 0.0 || (bary_weights[U] + bary_weights[V]) > 1.0)
		return (FLT_MAX);
	dist = vec3_dot(obj->triangle.edges[1], bary_vec[QVEC]) * inv_det;
	if (dist < EPSILON)
		return (FLT_MAX);
	obj->triangle.uv.x = bary_weights[U];
	obj->triangle.uv.y = bary_weights[V];
	return (dist);
}
