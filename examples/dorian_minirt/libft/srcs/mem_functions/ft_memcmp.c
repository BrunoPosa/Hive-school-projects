/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:43:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/13 07:34:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;
	size_t			i;

	i = 0;
	s1_cpy = (unsigned char *) s1;
	s2_cpy = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n && s1_cpy[i] == s2_cpy[i])
			i++;
	if (i < n)
		return (s1_cpy[i] - s2_cpy[i]);
	return (0);
}
