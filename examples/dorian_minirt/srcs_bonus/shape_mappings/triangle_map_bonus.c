/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:09:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:48:24 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_bonus.h"
#include "objects_bonus.h"
#include <unistd.h>

t_vec2	triangle_map(t_vec3 *point, t_object *obj)
{
	float	w;
	t_vec2	uv;

	(void) point;
	w = 1.0f - obj->triangle.uv.x - obj->triangle.uv.y;
	uv = vec2_add(vec2_add(vec2_multf((t_vec2){0, 0}, obj->triangle.uv.x),
				vec2_multf((t_vec2){0, 1}, obj->triangle.uv.x)),
			vec2_multf((t_vec2){1, 0}, w));
	return (uv);
}
