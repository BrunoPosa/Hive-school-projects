/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:16:11 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/29 12:38:10 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "libft.h"
# include <math.h>

# ifndef FLT_MAX
#  define FLT_MAX 3.40282346638528859811704183484516925e+38F
# endif

typedef struct s_vec2
{
	float	x;
	float	y;
}			t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

typedef struct s_vec3_face
{
	int	v;
	int	t;
	int	n;
}			t_vec3_face;

typedef struct s_vec4
{
	float	v;
	float	x;
	float	y;
	float	z;
}			t_vec4;

// VECTOR MATHS

t_vec2	vec2_multf(const t_vec2 v, const float val);
t_vec2	vec2_addf(const t_vec2 v, const float val);
t_vec2	vec2_add(const t_vec2 v, const t_vec2 u);

t_vec3	vec3_add(const t_vec3 v, const t_vec3 u);
t_vec3	vec3_addf(const t_vec3 v, const float val);
t_vec3	vec3_sub(const t_vec3 v, const t_vec3 u);
float	vec3_mag(const t_vec3 v);
t_vec3	vec3_multf(const t_vec3 v, const float val);
float	vec3_dot(const t_vec3 v, const t_vec3 u);
t_vec3	vec3_cross(const t_vec3 v, const t_vec3 u);
t_vec3	vec3_reflect(const t_vec3 v, const t_vec3 normal);
t_vec3	vec3_compmult(const t_vec3 v, const t_vec3 u);
float	vec3_dist(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_neg(const t_vec3 v);
void	vec3_normalize(t_vec3 *v);

t_vec4	vec4_add(const t_vec4 v, const t_vec4 u);
t_vec4	vec4_addf(const t_vec4 v, const float val);
t_vec4	vec4_sub(const t_vec4 v, const t_vec4 u);
float	vec4_mag(const t_vec4 v);
t_vec4	vec4_multf(const t_vec4 v, const float val);
float	vec4_dot(const t_vec4 v, const t_vec4 u);
t_vec4	vec4_propadd(const t_vec4 v1, const t_vec4 v2, const float prop);
t_vec4	vec4_compmult(const t_vec4 v, const t_vec4 u);
void	vec4_clamp(t_vec4 *v, const float min, const float max);
void	vec4_scale(t_vec4 *v, const t_range old, const t_range new);
t_vec4	vec4_add_array(const t_vec4 v, const t_vec4 *array,
			const size_t arr_len);

void	ft_rgbtonorm(t_vec4 *colour);
t_vec4	ft_trgbtov4(int colour[4]);
t_vec4	ft_int32tov4(int32_t colour);
int32_t	vec4_toint32(t_vec4 colour);

#endif
