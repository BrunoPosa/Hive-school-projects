/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:06:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/13 07:34:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	res;
	size_t	src_len;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	res = 0;
	if (dstsize > dst_len)
		res = src_len + dst_len;
	else
		return (src_len + dstsize);
	while (*src && (dst_len + 1) < dstsize)
	{
		dst[dst_len] = *src++;
		dst_len++;
	}
	dst[dst_len] = '\0';
	return (res);
}
