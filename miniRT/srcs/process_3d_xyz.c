/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_3d_xyz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:16:58 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 13:35:44 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
[-1,1], [-1,1], [-1,1]

minimum = -1
maximum = 1
3x floats
2x commas
*/

int	process_xyz_3d(t_list *current)
{
	int		i;
	char	**xyz;
	char	*sub_string;
	int		atoi_overflow;

	xyz = NULL;
	atoi_overflow = 0;
	i = len_until_space(current->p);
	sub_string = ft_substr(current->p, 0, i);
	if (!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (free(sub_string), ret_error(E_XYZ_3D_CHARS, current));
	if (count_commas_between(sub_string) != 2)
		return (free(sub_string), ret_error(E_XYZ_3D_COMMA, current));
	xyz = ft_split(sub_string, ',');
	if (!xyz)
		return (free(sub_string), ret_error(E_SPLIT, current));
	if (!is_number_valid(xyz[0]) || !is_number_valid(xyz[1]) || !is_number_valid(xyz[2]))
		return (free(sub_string), ret_error(E_XYZ_3D_CHARS, current));
	current->xyz_3d.x = ft_atod(xyz[0], &atoi_overflow);
	current->xyz_3d.y = ft_atod(xyz[1], &atoi_overflow);
	current->xyz_3d.z = ft_atod(xyz[2], &atoi_overflow);
	free_array(xyz);
	if (atoi_overflow)
        return (free(sub_string), ret_error(E_XYZ_RANGE, current));
	current->p = current->p + i;
	current->p = skip_space(current->p);
free(sub_string);

return (E_SUCCESS);
}
