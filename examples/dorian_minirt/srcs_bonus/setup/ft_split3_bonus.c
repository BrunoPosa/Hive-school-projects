/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:08:56 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/26 17:09:06 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minirt_bonus.h"

static int	count_words(char const *s, char c, char d)
{
	int	index;
	int	word;

	index = 0;
	word = 0;
	while (s && s[index])
	{
		if (s[index] != c && s[index] != d)
		{
			word++;
			while (s[index] != c && s[index] != d && s[index])
				index++;
		}
		else
			index++;
	}
	return (word);
}

static void	free_all(char **str_array, int out_index)
{
	while (str_array)
	{
		free(str_array[out_index]);
		out_index--;
	}
}

static int	word_length(char const *str, char c, int index, char d)
{
	int	size;

	size = 0;
	while (str[index] != c && str[index] != d && str[index])
	{
		size++;
		index++;
	}
	return (size);
}

char	**ft_split3(char const *s, char c, char d)
{
	int		index;
	int		word;
	char	**str_array;
	int		out_index;

	index = 0;
	out_index = -1;
	word = count_words(s, c, d);
	str_array = (char **)malloc((word + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	while (++out_index < word)
	{
		while (s[index] == c || s[index] == d)
			index++;
		str_array[out_index] = ft_substr(s, index, word_length(s, c, index, d));
		if (!str_array[out_index])
		{
			free_all(str_array, out_index);
			return (NULL);
		}
		index += word_length(s, c, index, d);
	}
	str_array[out_index] = 0;
	return (str_array);
}
