/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:56:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:16:22 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include "libft_bonus.h"

void	vec4_scale(t_vec4 *v, const t_range old, const t_range new)
{
	(*v).v = 1;
	(*v).x = ft_scale((*v).x, old, new);
	(*v).y = ft_scale((*v).y, old, new);
	(*v).z = ft_scale((*v).z, old, new);
}
