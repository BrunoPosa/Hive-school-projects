/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:27:30 by djagusch          #+#    #+#             */
/*   Updated: 2022/11/15 13:29:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_c2(unsigned long long ptr, int fd)
{
	char		*hex_add;
	int			length;

	ft_putstr_fd("0x", fd);
	if (!ptr)
		return (ft_putchar_c('0') + 2);
	hex_add = ft_dec_hexstr(ptr);
	if (!hex_add)
		return (return_null());
	ft_strlower(hex_add);
	length = ft_putstr_c2(hex_add, fd);
	free(hex_add);
	return (length + 2);
}
