/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:43:58 by ohertzbe          #+#    #+#             */
/*   Updated: 2024/08/27 15:03:02 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

/*
	I = incoming vector
	N = normal vector, vector perpendicular to hit point
	I - 2.0 * dot(N, I) * N.
*/
t_vec	reflect(t_vec I, t_vec N)
{
	t_vec	norm;
	t_vec	reflection;

	norm = unit_vec(N);
	reflection = vec_mult(norm, dot_prod(norm, I) * 2.0);
	reflection = vec_sub(I, reflection);
	return (reflection);
}
