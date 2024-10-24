/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:13:00 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/28 10:23:36 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

int	parse_ulong(char *str, size_t *num)
{
	if (is_ulong(str) == 0)
	{
		error_msg("not a number!\n", 0);
		return (0);
	}
	*num = (size_t)ft_atoi(str);
	return (1);
}

int	parse_float(char *str, float *num)
{
	if (is_float(str) == 0)
	{
		error_msg("not a number!\n", 0);
		return (0);
	}
	*num = ft_atof(str);
	return (1);
}

int	check_comma(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == ',')
	{
		error_msg("invalid character!\n", 0);
		return (0);
	}
	return (1);
}

int	parse_vector(char *str, t_vec *v)
{
	char	**vec;

	if (check_comma(str) == 0)
		return (0);
	vec = ft_split(str, ',');
	if (doublelen(vec) != 3)
	{
		error_msg("vector should have only 3 coordinates!\n", 0);
		free_arr(vec);
		return (0);
	}
	if (is_float(vec[0]) == 0 || is_float(vec[1]) == 0 || is_float(vec[2]) == 0)
	{
		error_msg("not a number!\n", 0);
		free_arr(vec);
		return (0);
	}
	v->x = ft_atof(vec[0]);
	v->y = ft_atof(vec[1]);
	v->z = ft_atof(vec[2]);
	free_arr(vec);
	return (1);
}
