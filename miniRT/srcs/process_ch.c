/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:30:09 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:41:44 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_ch(t_list *current)
{
	int		len;
	int		atoi_overflow;
	char	*sub_string;

	atoi_overflow = 0;
	len = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, len);
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS4))
		return (free_return(sub_string, E_FLOAT_CHARS));
	current->h = ft_atod(sub_string, &atoi_overflow);
	current->p = skip_space(current->p + len);
	free(sub_string);
	if (atoi_overflow || current->h <= EPSILON)
		return (E_CYLINDER_CH);
	return (E_SUCCESS);
}
