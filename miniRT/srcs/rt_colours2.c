/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_colours2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:42:35 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 19:39:46 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
	If any channel is > 255.0f we scale each channel down so that the biggest one
	is 255.0 and other values stay proportional.
*/
t_colour	scale_colour_channels(t_colour a)
{
	float		max_value;
	float		scale;

	if (a.r > 255.0f || a.g > 255.0f || a.b > 255.0f)
	{
		max_value = fmaxf(fmaxf(a.r, a.g), a.b);
		scale = 255.0f / max_value;
		a.r *= scale;
		a.g *= scale;
		a.b *= scale;
	}
	return (a);
}
