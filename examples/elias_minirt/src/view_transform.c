/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:05:34 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/16 11:04:54 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static t_matrix	*orient(float *left, float *true_up, float *forw, float *from)
{
	t_matrix	*m;
	t_matrix	*result;
	t_matrix	*t;
	float		*neg_for;

	neg_for = negate_vector(forw);
	free(forw);
	if (!neg_for)
		return (NULL);
	m = create_populated_matrix(left, true_up, neg_for, create_point(0, 0, 0));
	if (!m)
		return (NULL);
	t = create_translate(-from[0], -from[1], -from[2]);
	free(from);
	if (!t)
	{
		clean_matrix(m, 4);
		return (NULL);
	}
	result = matrix_multiply(m, t, 1);
	return (result);
}

t_matrix	*view_transform(float *from, float *to, float *up)
{
	float	*forward;
	float	*left;
	float	*true_up;
	float	*upn;

	forward = tuple_subs(to, from);
	if (!forward)
		return (NULL);
	forward = normalize(forward, 1);
	if (!forward)
		return (NULL);
	upn = normalize(up, 1);
	if (!upn)
		return (NULL);
	left = vector_cross_prod(forward, upn);
	if (!left)
		return (NULL);
	true_up = vector_cross_prod(left, forward);
	if (!true_up)
		return (NULL);
	free(upn);
	free(to);
	return (orient(left, true_up, forward, from));
}
