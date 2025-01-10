/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dist_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:11:26 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:32:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"

float	vec3_dist(const t_vec3 v1, const t_vec3 v2)
{
	return (vec3_mag(vec3_sub(v1, v2)));
}
