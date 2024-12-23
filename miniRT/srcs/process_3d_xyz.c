/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_3d_xyz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:16:58 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 04:10:28 by jwadding         ###   ########.fr       */
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

static void	p_xyz_3d_helper1(char ***xyz, int *atoi_overflow, int *i, char *p)
{
	xyz = NULL;
	(void)xyz;
	atoi_overflow = 0;
	(void)atoi_overflow;
	*i = len_until_space(p);
}

static int	p_xyz_3d_helper2(char *sub_string)
{
	if (!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (free(sub_string), E_XYZ_3D_CHARS);
	if (count_commas_between(sub_string) != 2)
		return (free(sub_string), E_XYZ_3D_COMMA);
	return (1);
}

int	process_xyz_3d(t_list *current)
{
	int		i;
	// int		status;
	char	**xyz;
	char	*sub_string;
	int		atoi_overflow;

	// status = 0;

	p_xyz_3d_helper1(&xyz, &atoi_overflow, &i, current->p);
	sub_string = ft_substr(current->p, 0, i);
	
	if (!p_xyz_3d_helper2(sub_string))
		printf("xyz3d problem\n");
	
	// status = p_xyz_3d_helper2(sub_string);
	// if (status)
	// 	return (free(sub_string), status);
		
	xyz = ft_split(sub_string, ',');
	if (!xyz)
		return (free(sub_string), E_SPLIT);
		
	if (!is_n_valid(xyz[0]) || !is_n_valid(xyz[1]) || !is_n_valid(xyz[2]))
		return (free(sub_string), E_XYZ_3D_CHARS);
		
	current->xyz_3d.x = ft_atod(xyz[0], &atoi_overflow);
	current->xyz_3d.y = ft_atod(xyz[1], &atoi_overflow);
	current->xyz_3d.z = ft_atod(xyz[2], &atoi_overflow);
	
	free_array(xyz);
	
	if (atoi_overflow)
		return (free(sub_string), E_XYZ_RANGE);
		
	//add a normalization check: sqrt(x^2 + y^2 + z^2) == 1
	
	current->p = current->p + i;
	current->p = skip_space(current->p);
	free(sub_string);
	return (E_SUCCESS);
}
