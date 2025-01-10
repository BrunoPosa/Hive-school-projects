/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:25:44 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/13 07:34:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cpy;
	size_t			i;

	i = 0;
	cpy = (unsigned char *) s;
	while (i < n && cpy[i] != (unsigned char) c && cpy[i] != '\0')
		i++;
	if ((cpy[i] != '\0' || cpy[i] == (unsigned char) c) && i < n)
		return (cpy + i);
	return (NULL);
}
