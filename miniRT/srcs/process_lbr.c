/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:36:52 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 20:38:22 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// needs to be between 0.0. and 1.0
int	process_lbr(t_list *current)
{
	int		i;
	int		atoi_overflow;
	char	*sub_string;

	i = len_until_space(current->p);
	atoi_overflow = 0;
	sub_string = ft_substr(current->p, 0, i);
	if (sub_string == NULL)
		return (ret_error(E_MALLOC, current));
	if (!only_legal_chars(sub_string, LEGAL_CHARS4) || !is_n_valid(sub_string))
		return (free(sub_string), ret_error(E_ALR_CHARS, current));
	current->lbr = ft_atod(current->p, &atoi_overflow);
	if (current->lbr < 0 || current->lbr > 1 || atoi_overflow)
		return (free(sub_string), ret_error(E_ALR_RANGE, current));
	current->p = current->p + i;
	current->p = skip_space(current->p);
	free(sub_string);
	return (E_SUCCESS);
}
