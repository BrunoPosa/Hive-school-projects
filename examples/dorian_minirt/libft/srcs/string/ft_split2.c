/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:09:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/10 15:09:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *s);

static int	ft_get_quotes(char const *s, size_t *index, size_t *i, size_t *size)
{
	char	quote;

	quote = s[*index - 1];
	(*i)++;
	(*size) -= 1;
	while (s[*index] != quote && s[*index])
	{
		(*index)++;
		(*size)++;
	}
	if (!s[*index])
	{
		(*size) = 0;
		return (0);
	}
	return (1);
}

static void	ft_word_len(char const *s, size_t *i, size_t *size)
{
	size_t	quote_flag;
	size_t	index;

	index = *i;
	quote_flag = 0;
	while (!ft_isspace(s[index]) && s[index] && !quote_flag)
	{
		index++;
		(*size)++;
		if (s[index - 1] == '\'' || s[index - 1] == '\"')
			quote_flag = ft_get_quotes(s, &index, i, size);
	}
}

static void	ft_get_word2(char **str, char const *s, size_t *i)
{
	size_t	len;
	size_t	size;

	len = 0;
	size = 0;
	ft_word_len(s, i, &size);
	*str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return ;
	while (len < size && s[*i])
	{
		(*str)[len++] = (char) s[*i];
		(*i)++;
	}
	(*str)[size] = '\0';
}

static void	ft_do_splitting(char **result, char const *s, int word, size_t *i)
{
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (!ft_isspace(s[*i]) && s[*i])
	{
		ft_get_word2(&result[word], s, i);
		(*i)++;
	}
	if (!result[word] || !result[word][0])
		ft_free_array(&result, word);
}

char	**ft_split2(char const *s)
{
	char	**result;
	size_t	i;
	size_t	n_words;
	size_t	word;

	word = 0;
	i = 0;
	if (!s)
		return (NULL);
	n_words = ft_count_words(s);
	result = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!result)
		return (NULL);
	while (word < n_words)
		ft_do_splitting(result, s, word++, &i);
	result[word] = NULL;
	return (result);
}
