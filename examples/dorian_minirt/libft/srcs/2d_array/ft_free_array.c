/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:20:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/13 13:40:32 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_array(char ***array, size_t elements)
{
	int	i;

	i = 0;
	while (i < (int) elements)
	{
		if ((*array)[i])
			ft_free((*array)[i]);
		(*array)[i++] = NULL;
	}
	ft_free(*array);
	array = NULL;
	return (NULL);
}

void	*ft_free_anyarray(void ***array, size_t elements)
{
	int	i;

	i = 0;
	while (i < (int) elements)
	{
		if ((*array)[i])
			ft_free((*array)[i]);
		(*array)[i++] = NULL;
	}
	ft_free(*array);
	array = NULL;
	return (NULL);
}
