/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:47:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/08 12:45:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_scale(float value, t_range range_old, t_range range_new)
{
	float	scaled_val;

	scaled_val = (value - range_old.min);
	scaled_val /= (range_old.max - range_old.min);
	scaled_val *= (range_new.max - range_new.min);
	scaled_val += range_new.min;
	return (scaled_val);
}
