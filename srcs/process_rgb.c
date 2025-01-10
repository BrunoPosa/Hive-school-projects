/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:15:44 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static bool	import_rgb_values(char **rgb, t_list *current)
{
	int	atoi_overflow;

	atoi_overflow = 0;
	current->rgb.r = ft_atoi(rgb[0], &atoi_overflow);
	current->rgb.g = ft_atoi(rgb[1], &atoi_overflow);
	current->rgb.b = ft_atoi(rgb[2], &atoi_overflow);
	if (atoi_overflow || current->rgb.r < 0 || current->rgb.r > 255
		|| current->rgb.g < 0 || current->rgb.g > 255
		|| current->rgb.b < 0 || current->rgb.b > 255)
		return (E_RGB_RANGE);
	return (E_SUCCESS);
}

int	process_rgb(t_list *current)
{
	int		len;
	char	**rgb;
	char	*sub_string;

	len = len_until_space(current->p);
	rgb = NULL;
	sub_string = ft_substr(current->p, 0, len);
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS5))
		return (free_return(sub_string, E_RGB_CHARS));
	if (count_commas_between(sub_string) != 2)
		return (free_return(sub_string, E_RGB_COMMA));
	rgb = ft_split(sub_string, ',');
	free(sub_string);
	if (!rgb)
		return (E_SPLIT);
	if (import_rgb_values(rgb, current))
		return (free_arr_return(rgb, E_RGB_RANGE));
	current->p = skip_space(current->p + len);
	free_array(rgb);
	return (E_SUCCESS);
}
