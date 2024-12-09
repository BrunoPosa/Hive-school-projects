/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:33:52 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 20:34:21 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
// fov - [0-180]
int
*/

int	process_fov(t_list *current)
{
	int		i;
	int		atoi_overflow;
	char	*sub_string;

	atoi_overflow = 0;
	i = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, i);
	if (sub_string == NULL)
		return (ret_error(E_MALLOC, current));
	if (!only_legal_chars(sub_string, LEGAL_CHARS6))
		return (free(sub_string), ret_error(E_UINT_CHARS, current));
	current->fov = ft_atoi(sub_string, &atoi_overflow);
	if (atoi_overflow || current->fov > 180)
		return (free(sub_string), ret_error(E_FOV_RANGE, current));
	current->p = current->p + i;
	current->p = skip_space(current->p);
	free(sub_string);
	return (E_SUCCESS);
}
