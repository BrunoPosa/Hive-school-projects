/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:15:44 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/22 18:39:45 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
find_len_until_space()
int	only_legal_chars(char *s, char *LEGAL_CHARS4)

[0-255], [0-255], [0-255]

minimum = 0
maximum = 255
3x unsigned ints
2x commas
max 3 digits
only allowed characters are numbers and commas
*/

int	process_rgb(t_list *current)
{
	int		i;
	int		atoi_overflow;
	char	*sub_string;
	char	**rgb;

	rgb = NULL;
	atoi_overflow = 0;
	i = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, i);
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS5))
		return (free(sub_string), E_RGB_CHARS);
	if (count_commas_between(sub_string) != 2)
		return (free(sub_string), E_RGB_COMMA);
	rgb = ft_split(sub_string, ',');
	if (!rgb)
		return (free(sub_string), E_SPLIT);
	current->rgb.r = ft_atoi(rgb[0], &atoi_overflow);
	current->rgb.g = ft_atoi(rgb[1], &atoi_overflow);
	current->rgb.b = ft_atoi(rgb[2], &atoi_overflow);
	free_array(rgb);
	if (atoi_overflow || current->rgb.r < 0 || current->rgb.r > 255
		|| current->rgb.g < 0 || current->rgb.g > 255
		|| current->rgb.b < 0 || current->rgb.b > 255)
		return (free(sub_string), E_RGB_RANGE);
	current->p = current->p + i;
	current->p = skip_space(current->p);
	free(sub_string);
	return (E_SUCCESS);
}
