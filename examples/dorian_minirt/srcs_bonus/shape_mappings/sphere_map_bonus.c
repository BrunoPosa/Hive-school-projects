/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:53:02 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 14:02:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "vector_math_bonus.h"
#include <math.h>
#include "patterns_bonus.h"

t_vec2	spherical_map(t_vec3 *point, t_object *obj)
{
	float	angle;
	float	polar_angle;
	t_vec3	transl_point;
	t_vec2	uv;

	transl_point = vec3_sub(*point, obj->sphere.pos);
	angle = atan2f(transl_point.x, transl_point.z);
	polar_angle = acosf(transl_point.y / obj->sphere.radius);
	uv.x = angle * M_1_DIV_2PI;
	uv.x = 1 - ft_frac(uv.x + 1);
	uv.y = polar_angle * M_1_DIV_PI;
	return (uv);
}
