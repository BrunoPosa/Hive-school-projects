/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:22:41 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/26 17:22:43 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include "vector_math.h"
#include "scene.h"
#include "shaders.h"

#ifndef M_PI_4
# define M_PI_4 0.78539816339744830962
#endif
#ifndef DEG2RAD
# define DEG2RAD 0.008726646259971647737
#endif

#ifndef X
# define X 0
#endif
#ifndef Y
# define Y 1
#endif
#ifndef R
# define R 2
#endif

t_ray	create_primary_ray(const t_camera *cam, const t_vec2 pxl)
{
	float	norm_coord_x;
	float	norm_coord_y;
	t_ray	primary_ray;
	float	fisheye[3];
	float	phi;

	norm_coord_x = (1.0f - (2.0f * (pxl.x + 0.5f) / WIDTH)) * \
		cam->aspect_ratio * tan(cam->fov * DEG2RAD);
	norm_coord_y = (1.0f - (2.0f * (pxl.y + 0.5f) / HEIGHT)) * \
		tan(cam->fov * DEG2RAD);
	fisheye[R] = sqrt(norm_coord_x * norm_coord_x + norm_coord_y \
		* norm_coord_y);
	phi = atan2(norm_coord_y, norm_coord_x);
	fisheye[R] = fisheye[R] * 0.5f;
	fisheye[X] = fisheye[R] * cos(phi);
	fisheye[Y] = fisheye[R] * sin(phi);
	primary_ray.origin = cam->pos;
	primary_ray.direction = vec3_add(cam->dir,
			vec3_add(vec3_multf(cam->right, fisheye[X]),
				vec3_multf(cam->up, fisheye[Y])));
	vec3_normalize(&primary_ray.direction);
	return (primary_ray);
}
