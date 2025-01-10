/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:23:39 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:45:34 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_sd(t_list *current)
{
	int		atoi_overflow;
	int		len;
	char	*sub_string;

	atoi_overflow = 0;
	len = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, len);
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS7) || !is_n_valid(sub_string))
		return (free_return(sub_string, E_FLOAT_CHARS));
	current->d = ft_atod(sub_string, &atoi_overflow);
	current->p = skip_space(current->p + len);
	free(sub_string);
	if (atoi_overflow || current->d <= EPSILON)
		return (E_SPHERE_SD);
	return (E_SUCCESS);
}
