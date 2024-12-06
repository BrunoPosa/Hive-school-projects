/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:56:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:16:16 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "libft.h"

void	vec4_scale(t_vec4 *v, const t_range old, const t_range new)
{
	(*v).v = 1;
	(*v).x = ft_scale((*v).x, old, new);
	(*v).y = ft_scale((*v).y, old, new);
	(*v).z = ft_scale((*v).z, old, new);
}
