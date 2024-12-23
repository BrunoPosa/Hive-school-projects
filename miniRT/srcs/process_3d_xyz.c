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

static bool	is_normalized(t_vec xyz)
{
	if (fabs((pow(xyz.x, 2.0) + pow(xyz.y, 2.0) + pow(xyz.z, 2.0)) - 1.0f)
		> EPSILON)
		return (FALSE);
	return (TRUE);
}

static int	import_nums(t_list *current, char **xyz, int *status)
{
	int	atoi_overflow;

	atoi_overflow = 0;
	if (!is_n_valid(xyz[0]) || !is_n_valid(xyz[1]) || !is_n_valid(xyz[2]))
	{
		*status = E_XYZ_3D_CHARS;
		return (free_arr_return(xyz, E_XYZ_3D_CHARS));
	}
	current->xyz_3d.x = ft_atod(xyz[0], &atoi_overflow);
	current->xyz_3d.y = ft_atod(xyz[1], &atoi_overflow);
	current->xyz_3d.z = ft_atod(xyz[2], &atoi_overflow);
	free_array(xyz);
	if (atoi_overflow)
	{
		*status = E_XYZ_RANGE;
		return (E_XYZ_RANGE);
	}
	return (E_SUCCESS);
}

int	process_xyz_3d(t_list *current)
{
	int		len;
	int		status;
	char	**xyz;
	char	*sub_string;

	len = len_until_space(current->p);
	status = 0;
	xyz = NULL;
	sub_string = ft_substr(current->p, 0, len);
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
	if (import_nums(current, xyz, &status))
		return(status);
	if (!is_normalized(current->xyz_3d))
		return (E_XYZ_3D_NORMALIZE);
	current->p = skip_space(current->p + len);
	return (E_SUCCESS);
}
