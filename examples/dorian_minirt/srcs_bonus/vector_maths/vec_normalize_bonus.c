/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:14:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 16:56:59 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include <math.h>

void	vec3_normalize(t_vec3 *v)
{
	float	mag;

	mag = sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	v->x /= mag;
	v->y /= mag;
	v->z /= mag;
}

void	vec2_normalize(t_vec2 *v)
{
	float	mag;

	mag = sqrtf((v->x * v->x) + (v->y * v->y));
	v->x /= mag;
	v->y /= mag;
}
