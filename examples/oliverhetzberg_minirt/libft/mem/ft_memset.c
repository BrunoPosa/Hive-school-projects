/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:19:06 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 16:19:07 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*(p++) = (unsigned char)c;
		n--;
	}
	return (s);
}
