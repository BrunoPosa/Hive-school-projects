/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:33:36 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 13:33:38 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/utils.h"

int	is_ulong(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	is_color(char **str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_atoi(str[i]) < 0 || ft_atoi(str[i]) > 255)
		{
			error_msg("vector's values need to be in interval [0,255]!\n", 0);
			return (0);
		}
		i++;
	}
	return (1);
}
