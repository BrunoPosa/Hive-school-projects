/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:50:38 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/09 08:18:04 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	str_length;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	str_length = ft_strlen(s);
	if (start >= str_length)
		return (ft_strdup(""));
	substring = (char *) malloc(sizeof(char) * (ft_min(len, str_length) + 1));
	if (!substring)
		return (NULL);
	while (s[start + i] && i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
