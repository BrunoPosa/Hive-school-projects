/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_3d_xyz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:16:58 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 04:25:52 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

static int	import_values(t_list *current, char **xyz)
{
	int	atoi_overflow;

	atoi_overflow = 0;
	current->xyz_3d.x = ft_atod(xyz[0], &atoi_overflow);
	current->xyz_3d.y = ft_atod(xyz[1], &atoi_overflow);
	current->xyz_3d.z = ft_atod(xyz[2], &atoi_overflow);
	if (atoi_overflow)
		return (E_XYZ_RANGE);
	return (E_SUCCESS);
}

int	process_xyz_3d(t_list *current)
{
	char	**xyz;
	char	*sub_string;

	xyz = NULL;
	sub_string = ft_substr(current->p, 0, len_until_space(current->p));
	if (!sub_string)
		return (E_MALLOC);
	if (!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (free_return(sub_string, E_XYZ_3D_CHARS));
	if (count_commas_between(sub_string) != 2)
		return (free_return(sub_string, E_XYZ_3D_COMMA));
	xyz = ft_split(sub_string, ',');
	free(sub_string);
	if (!xyz)
		return (E_SPLIT);
	if (!is_n_valid(xyz[0]) || !is_n_valid(xyz[1]) || !is_n_valid(xyz[2]))
		return (free_arr_return(xyz, E_XYZ_3D_CHARS));
	if (import_values(current, xyz))
		return(free_arr_return(xyz, E_XYZ_RANGE));
	free_array(xyz);
	if (fabs((pow(current->xyz_3d.x, 2) + pow(current->xyz_3d.y, 2) +
		pow(current->xyz_3d.z, 2)) - 1.0f) > EPSILON)
		return (E_XYZ_3D_NORMALIZE);
	current->p = skip_space(current->p + len_until_space(current->p));
	return (E_SUCCESS);
}
