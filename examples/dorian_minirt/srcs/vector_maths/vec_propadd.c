/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_propadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:44:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 15:53:16 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec4	vec4_propadd(const t_vec4 v1, const t_vec4 v2, const float prop)
{
	t_vec4	new_vec;
	float	prop2;

	prop2 = 1 - prop;
	new_vec.v = 1;
	new_vec.x = v1.x * prop + v2.x * prop2;
	new_vec.y = v1.y * prop + v2.y * prop2;
	new_vec.z = v1.z * prop + v2.z * prop2;
	return (new_vec);
}
