/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:36:52 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_lbr(t_list *current)
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
		return (free_return(sub_string, E_LBR_CHARS));
	current->lbr = ft_atod(sub_string, &atoi_overflow);
	free(sub_string);
	if (atoi_overflow || current->lbr < 0.0 || current->lbr > 1.0)
		return (E_LBR_RANGE);
	current->p = skip_space(current->p + len);
	return (E_SUCCESS);
}
