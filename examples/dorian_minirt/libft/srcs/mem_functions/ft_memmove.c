/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:49:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/11 15:44:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_move(void **dst, const void **src, size_t len, int ind)
{
	size_t			i;
	unsigned char	*dst_cpy;
	unsigned char	*src_cpy;

	dst_cpy = (unsigned char *) *dst;
	src_cpy = (unsigned char *) *src;
	i = 0;
	if (ind)
	{
		while (i < len)
		{	
			dst_cpy[i] = src_cpy[i];
			i++;
		}
	}
	else
	{
		while (len--)
			dst_cpy[len] = src_cpy[len];
		dst_cpy[0] = src_cpy[0];
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!src && !dst)
		return (NULL);
	if (!len)
		return (dst);
	if (dst < src)
		ft_move(&dst, &src, len, 1);
	else
		ft_move(&dst, &src, len, 0);
	return (dst);
}
