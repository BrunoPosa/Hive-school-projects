/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which_extr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:10:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/09 08:25:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_which_max(int *arr, size_t len)
{
	int		res;
	size_t	i;

	res = arr[0];
	i = 1;
	while (i < len)
	{
		if (res < arr[i])
			res = arr[i];
		i++;
	}
	return (res);
}

int	ft_which_min(int *arr, size_t len)
{
	int		res;
	size_t	i;

	res = arr[0];
	i = 1;
	while (i < len)
	{
		if (res > arr[i])
			res = arr[i];
		i++;
	}
	return (res);
}
