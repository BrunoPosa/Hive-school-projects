/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brick_pattern_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:10:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:32:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_bonus.h"
#include "vector_math_bonus.h"

#ifndef X
# define X 0
#endif
#ifndef Y
# define Y 1
#endif

t_vec4	get_brick(t_texture *texture, t_vec2 uv)
{
	int	t[2];
	int	edge;
	int	oddity;

	(void) texture;
	t[X] = (int) 10 * uv.x;
	t[Y] = (int) 10 * uv.y;
	oddity = (t[X] & 0x01) == (t[Y] & 0x01);
	edge = ((fabsf(10 * uv.x - t[X]) < 0.1 && oddity)
			|| fabs(10 * uv.y - t[Y]) < 0.1);
	if (edge)
		return ((t_vec4){1, 0.9568, 0.9490, 0.9490});
	return ((t_vec4){1, 0.62745, 0.21176, 0.13725});
}
