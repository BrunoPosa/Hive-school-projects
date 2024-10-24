/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:20:52 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 16:20:53 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		i;

	if (!str)
		return (NULL);
	dest = malloc(ft_strlen(str) + 1);
	i = 0;
	if (dest == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
