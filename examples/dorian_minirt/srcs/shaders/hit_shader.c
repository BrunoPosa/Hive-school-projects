/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/28 12:56:10 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

t_vec4	hit_shader(const t_scene *scene,
		const t_hitresult *hit, const t_light_info *light_info)
{
	t_vec4	col[5];
	int		num;

	num = 0;
	ft_bzero(col, 5 * sizeof(t_vec4));
	col[ambient] = vec4_multf(scene->amb.colour, scene->amb.ratio);
	col[ambient] = vec4_compmult(hit->colour, col[ambient]);
	while (num < scene->n_lights)
	{
		if (scene->distances[num] >= EPSILON)
		{
			col[diffuse] = vec4_compmult(hit->colour,
					light_info->colour);
		}
		col[final] = vec4_add(col[diffuse], col[final]);
		num++;
	}
	col[final] = vec4_multf(col[final], 1.0f / scene->n_lights);
	col[final] = vec4_add(col[ambient], col[final]);
	return (col[final]);
}
