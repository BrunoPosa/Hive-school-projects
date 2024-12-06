/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:05:34 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/13 07:34:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_needle(const char *haystack, const char *needle,
					size_t len, size_t i)
{
	size_t	j;

	j = 0;
	while (haystack[i + j] != '\0' && haystack[i + j] == needle[j]
		&& (i + j) < len)
		j++;
	if (needle[j] == '\0')
		return (i);
	return (-1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	long	check;

	i = 0;
	check = -1;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (i < len && haystack[i] != '\0')
	{
		while (haystack[i] != '\0' && haystack[i] != needle[0] && i < len)
			i++;
		if (haystack[i] != '\0' && i < len)
		{
			check = ft_find_needle(haystack, needle, len, i);
			if (check >= 0)
				return ((char *)(haystack + check));
			i++;
		}
	}
	return (NULL);
}
