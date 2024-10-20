/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:21:17 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 16:21:18 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	char	*cur;
	int		len;

	s = (char *)str;
	len = ft_strlen(s);
	cur = s + len;
	while (*cur != (unsigned char)c)
	{
		if (cur == s)
			return (NULL);
		cur--;
	}
	return (cur);
}
