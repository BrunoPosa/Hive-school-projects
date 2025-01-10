/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:41:47 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:05:38 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	procedural_bump(float x, float y, float z)
{
	return (sin(x * 10.0) * sin(y * 10.0) * sin(z * 10.0));
}

float	*perturb_normal(float *normal, float *point)
{
	float	bump_value;
	float	*p_normal;

	bump_value = procedural_bump(point[0], point[1], point[2]);
	p_normal = create_vector(0, 0, 0);
	if (!p_normal)
		return (NULL);
	p_normal[0] = normal[0] + bump_value;
	p_normal[1] = normal[1] + bump_value;
	p_normal[2] = normal[2] + bump_value;
	p_normal = normalize(p_normal, 1);
	free(normal);
	return (p_normal);
}
