/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:49:26 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

float	*reflect(float *vector, float *normal)
{
	float	r;
	float	*sca_mult_tuple;
	float	*result;

	r = 2 * dot_product(vector, normal);
	sca_mult_tuple = scalar_multi_tuple(normal, r);
	result = tuple_subs(vector, sca_mult_tuple);
	free(sca_mult_tuple);
	return (result);
}
