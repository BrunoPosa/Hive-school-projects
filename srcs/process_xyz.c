/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_xyz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:27:10 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	import_xyz_values(t_list *current, char **xyz, int *atoi_overflow)
{
	current->xyz.x = ft_atod(xyz[0], atoi_overflow);
	current->xyz.y = ft_atod(xyz[1], atoi_overflow);
	current->xyz.z = ft_atod(xyz[2], atoi_overflow);
}

int	process_xyz(t_list *current)
{
	int		atoi_overflow;
	char	**xyz;
	char	*sub_string;

	atoi_overflow = 0;
	xyz = NULL;
	sub_string = ft_substr(current->p, 0, len_until_space(current->p));
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (free_return(sub_string, E_XYZ_CHARS));
	if (count_commas_between(sub_string) != 2)
		return (free_return(sub_string, E_XYZ_COMMA));
	xyz = ft_split(sub_string, ',');
	free(sub_string);
	if (!xyz)
		return (E_SPLIT);
	if (!is_n_valid(xyz[0]) || !is_n_valid(xyz[1]) || !is_n_valid(xyz[2]))
		return (free_arr_return(xyz, E_XYZ_CHARS));
	import_xyz_values(current, xyz, &atoi_overflow);
	free_array(xyz);
	if (atoi_overflow)
		return (E_XYZ_RANGE);
	current->p = skip_space(current->p + len_until_space(current->p));
	return (E_SUCCESS);
}
