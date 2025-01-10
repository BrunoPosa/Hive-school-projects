/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:25:26 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 18:06:06 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *s)
{
	size_t	i;
	size_t	flag;
	size_t	quote_flag;

	i = 0;
	flag = 0;
	quote_flag = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !flag && !quote_flag)
		{
			flag = 1;
			i++;
		}
		else if (ft_isspace(*s))
			flag = 0;
		if (*s == '\'')
			quote_flag = (quote_flag + 1) % 2;
		s++;
	}
	return (i);
}
