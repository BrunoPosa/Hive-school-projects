/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:40:45 by ohertzbe          #+#    #+#             */
/*   Updated: 2024/08/27 21:36:58 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

float	hit_plane(t_vec normal, t_vec point, t_ray ray)
{
	float	denom;

	denom = dot_prod(normal, ray.direction);
	if (fabs(denom) > 0.00001f)
	{
		return (dot_prod(vec_sub(point, ray.start), normal) / denom);
	}
	return (-1.0);
}
