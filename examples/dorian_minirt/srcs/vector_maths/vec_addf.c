/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_addf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:20:27 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/26 17:02:18 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3	vec3_addf(const t_vec3 v, const float val)
{
	t_vec3	res;

	res.x = v.x + val;
	res.y = v.y + val;
	res.z = v.z + val;
	return (res);
}

t_vec4	vec4_addf(const t_vec4 v, const float val)
{
	t_vec4	res;

	res.v = 1;
	res.x = v.x + val;
	res.y = v.y + val;
	res.z = v.z + val;
	return (res);
}
