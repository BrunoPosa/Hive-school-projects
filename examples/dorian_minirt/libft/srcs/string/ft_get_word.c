/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:51:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 14:39:00 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_quote(char c)
{
	int	flag;

	flag = 0;
	if (c == '\"')
		flag = 1;
	else if (c == '\'')
		flag = 2;
	return (flag);
}

char	*ft_get_word(const char *str)
{
	int		i;
	int		len;
	int		flag;
	char	*word;

	if (!str)
		return (NULL);
	i = 0;
	len = 0;
	while (ft_isspace(str[i]))
		i++;
	flag = check_quote(str[i]);
	if (flag)
		i++;
	while (str[i] && (!(str[i] == '\"' && flag == 1)
			&& !(str[i] == '\'' && flag == 2)) && !ft_isspace(str[i]))
	{
		len++;
		i++;
	}
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &str[i - len], len + 1);
	return (word);
}
