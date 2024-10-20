/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:57 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 17:33:51 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

# include <unistd.h>
# include <stdio.h>
# include "../libft/headers/libft.h"

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

/* vector.c */
float	ft_sqr(float n);
float	vec_len(t_vec v);
t_vec	vec_add(t_vec v, t_vec u);
t_vec	vec_sub(t_vec v, t_vec u);
t_vec	vec_neg(t_vec v);

/* vector1.c */
t_vec	vec_mult(t_vec v, float a);
t_vec	vec_div(t_vec v, float a);
float	dot_prod(t_vec v, t_vec u);
t_vec	cross_prod(t_vec v, t_vec u);
t_vec	vec_norm(t_vec v);

/* vector2.c */
t_vec	unit_vec(t_vec v);

#endif
