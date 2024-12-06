/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:46:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 09:39:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	flag;

	i = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			i++;
		}	
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (i);
}

static void	ft_get_word2(char **str, char const *s, char c, size_t *i)
{
	size_t	len;
	size_t	size;
	size_t	index;

	len = 0;
	size = 0;
	index = *i;
	while (s[index] != c && s[index])
	{
		index++;
		size++;
	}	
	*str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return ;
	while (s[*i] != c && len < size && s[*i])
	{
		(*str)[len] = (char) s[*i];
		(*i)++;
		len++;
	}
	(*str)[len] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		n_words;
	size_t		word;
	size_t		i;

	i = 0;
	word = 0;
	if (!s)
		return (NULL);
	n_words = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!result)
		return (NULL);
	while (word < n_words)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			ft_get_word2(&result[word], s, c, &i);
		if (!result[word])
			return (ft_free_array(&result, word));
		word++;
	}
	result[word] = NULL;
	return (result);
}
