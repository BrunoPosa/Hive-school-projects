/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mag_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:12:26 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 15:01:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"

float	vec3_mag2(const t_vec3 v)
{
	float	val;

	val = vec3_dot(v, v);
	return (val);
}

float	vec4_mag2(const t_vec4 v)
{
	float	val;

	val = vec4_dot(v, v);
	return (val);
}

float	vec3_mag(const t_vec3 v)
{
	float	val;

	val = sqrt(vec3_dot(v, v));
	return (val);
}

float	vec4_mag(const t_vec4 v)
{
	float	val;

	val = sqrt(vec4_dot(v, v));
	return (val);
}
