/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:33:52 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_fov(t_list *current)
{
	int		len;
	int		atoi_overflow;
	char	*sub_string;

	len = len_until_space(current->p);
	atoi_overflow = 0;
	sub_string = ft_substr(current->p, 0, len);
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS6))
	{
		free(sub_string);
		return (E_UINT_CHARS);
	}
	current->fov = ft_atoi(sub_string, &atoi_overflow);
	free(sub_string);
	if (atoi_overflow || current->fov > 180)
		return (E_FOV_RANGE);
	current->p = skip_space(current->p + len);
	return (E_SUCCESS);
}
