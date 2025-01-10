/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_alr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:28:32 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_alr(t_list *current)
{
	int		len;
	int		atoi_overflow;
	char	*sub_string;

	len = len_until_space(current->p);
	atoi_overflow = 0;
	sub_string = ft_substr(current->p, 0, len);
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS4) || !is_n_valid(sub_string))
		return (free_return(sub_string, E_ALR_CHARS));
	current->alr = ft_atod(sub_string, &atoi_overflow);
	if (atoi_overflow || current->alr < 0.0 || current->alr > 1.0)
		return (free_return(sub_string, E_ALR_RANGE));
	current->p = skip_space(current->p + len);
	free(sub_string);
	return (E_SUCCESS);
}
