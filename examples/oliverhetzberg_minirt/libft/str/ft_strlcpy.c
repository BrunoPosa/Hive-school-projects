/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:21:04 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 16:21:05 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;

	src_length = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (i < src_length && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_length);
}

void	ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (i < n && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}
