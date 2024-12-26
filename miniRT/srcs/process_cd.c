/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:27:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:41:32 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_cd(t_list *current)
{
	int		atoi_overflow;
	int		len;
	char	*sub_string;

	atoi_overflow = 0;
	len = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, len);
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS4))
		return (free_return(sub_string, E_FLOAT_CHARS));
	current->d = ft_atod(sub_string, &atoi_overflow);
	current->p = skip_space(current->p + len);
	free(sub_string);
	if (atoi_overflow || current->d <= EPSILON)
		return (E_CYLINDER_CD);
	return (E_SUCCESS);
}
