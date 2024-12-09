/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_xyz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:27:10 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 23:41:06 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
[f], [f], [f]
2x commas
3x floats
*/

static void	process_xyz_helper1(int *atoi_overflow, int *i, char *p)
{
	*atoi_overflow = 0;
	*i = len_until_space(p);
}

static void	process_xyz_helper2(t_list *current, char **xyz, int *atoi_overflow)
{
	current->xyz.x = ft_atod(xyz[0], atoi_overflow);
	current->xyz.y = ft_atod(xyz[1], atoi_overflow);
	current->xyz.z = ft_atod(xyz[2], atoi_overflow);
}

int	process_xyz(t_list *current)
{
	int		i;
	char	*sub_string;
	int		atoi_overflow;
	char	**xyz;

	process_xyz_helper1(&atoi_overflow, &i, current->p);
	xyz = NULL;
	sub_string = ft_substr(current->p, 0, i);
	if (!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (free(sub_string), ret_error(E_XYZ_CHARS, current));
	if (count_commas_between(sub_string) != 2)
		return (free(sub_string), ret_error(E_XYZ_COMMA, current));
	xyz = ft_split(sub_string, ',');
	if (!xyz)
		return (free(sub_string), ret_error(E_SPLIT, current));
	if (!is_n_valid(xyz[0]) || !is_n_valid(xyz[1]) || !is_n_valid(xyz[2]))
		return (free(sub_string), ret_error(E_XYZ_CHARS, current));
	process_xyz_helper2(current, xyz, &atoi_overflow);
	free_array(xyz);
	if (atoi_overflow)
		return (free(sub_string), ret_error(E_XYZ_RANGE, current));
	current->p = current->p + i;
	current->p = skip_space(current->p);
	free(sub_string);
	return (E_SUCCESS);
}
