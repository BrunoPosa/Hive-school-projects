/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:21:24 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 17:34:43 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	size;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	s_len -= start;
	size = (s_len < len) * s_len + (s_len >= len) * len;
	sub = malloc(size + 1);
	if (!sub)
		return (0);
	ft_strlcpy(sub, (char *)s + start, size + 1);
	return (sub);
}

int	is_substr(char *str, char *sub)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != 0)
	{
		j = 0;
		if (str[i] == sub[0])
		{
			while (sub[j] != 0 && sub[j] == str[i])
			{
				i++;
				j++;
			}
			if (sub[j] == 0)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

void	ft_num_of_sub(const char *str, const char *sub, int *count)
{
	int	i;
	int	j;

	i = 0;
	if (!str || !sub)
		return ;
	while (str[i])
	{
		j = 0;
		if (str[i] == sub[j])
		{
			while (str[i])
			{
				if (str[i] != sub[j])
					break ;
				i++;
				j++;
			}
			if (sub[j] == 0)
				(*count)++;
		}
		else
			i++;
	}
}
