/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:56:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/13 07:34:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*s_cpy;

	s_cpy = (char *) s;
	i = ft_strlen(s);
	while (i >= 0 && s[i] != (unsigned char) c)
		i--;
	if (i >= 0)
		return (s_cpy + i);
	return (NULL);
}
