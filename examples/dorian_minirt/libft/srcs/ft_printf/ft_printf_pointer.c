/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:27:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/08 15:43:47 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_c(unsigned long long ptr)
{
	char	*hex_add;
	int		length;

	ft_putstr("0x");
	if (!ptr)
		return (ft_putchar_c('0') + 2);
	hex_add = ft_dec_hexstr(ptr);
	if (!hex_add)
		return (return_null());
	ft_strlower(hex_add);
	length = ft_putstr_c(hex_add);
	free(hex_add);
	return (length + 2);
}
