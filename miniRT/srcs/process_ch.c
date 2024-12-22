/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:30:09 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/22 21:45:34 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
if it allows negative, that means it is not there
float

same as sd, cd, ch
*/

int	process_ch(t_list *current)
{
	int		i;
	int		atoi_overflow;
	char	*sub_string;

	atoi_overflow = 0;
	i = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, i);
	if (!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (E_FLOAT_CHARS);
	current->h = ft_atod(sub_string, &atoi_overflow);
	current->p = current->p + i;
	current->p = skip_space(current->p);
	free(sub_string);
	return (E_SUCCESS);
}
