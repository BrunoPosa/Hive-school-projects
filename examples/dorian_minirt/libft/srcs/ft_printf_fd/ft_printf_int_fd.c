/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:26:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/02 15:10:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_c2(int n, int fd)
{
	int		count;

	count = 1;
	if (n == MY_INT_MIN)
	{
		ft_putstr_c2("-2147483648", fd);
		return (11);
	}
	if (n < 0)
	{
		count += ft_putchar_c2('-', fd);
		n = -1 * n;
	}
	if (n > 9)
	{
		count += ft_putnbr_c2(n * 0.1, fd);
		n %= 10;
	}
	if (n <= 9)
		ft_putchar_c2(n + '0', fd);
	return (count);
}
