/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:24:34 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/08 15:58:00 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_c2(unsigned int n, int c, int fd)
{
	char	*hex;
	int		length;

	if (n == 0)
		return (ft_putchar_c2('0', fd));
	hex = ft_dec_hexstr(n);
	if (!hex)
		return (return_null2(fd));
	if ('a' <= c && c <= 'z')
		ft_strlower(hex);
	length = ft_putstr_c2(hex, fd);
	free(hex);
	return (length);
}
