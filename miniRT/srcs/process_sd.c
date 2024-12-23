/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:23:39 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 04:16:30 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
we allow negatives, but that means it is not there
float
same as sd, cd, ch
*/

// // check within range
//     if (current->sd < 0.0 || current->sd > 1.0)
//         return (ret_error(E_ALR_RANGE, current));

int	process_sd(t_list *current)
{
	int		i;
	int		atoi_overflow;
	char	*sub_string;

	atoi_overflow = 0;
	i = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, i);
	if (!only_legal_chars(sub_string, LEGAL_CHARS7) || !is_n_valid(sub_string))
		return (E_FLOAT_CHARS);
	current->d = ft_atod(sub_string, &atoi_overflow);
	current->p = current->p + i;
	current->p = skip_space(current->p);
	free(sub_string);
	return (E_SUCCESS);
}
