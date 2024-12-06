/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:26:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/02 15:10:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_c(int n)
{
	int		count;

	count = 1;
	if (n == MY_INT_MIN)
	{
		ft_putstr_c("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		count += ft_putchar_c('-');
		n = -1 * n;
	}
	if (n > 9)
	{
		count += ft_putnbr_c(n * 0.1);
		n %= 10;
	}
	if (n <= 9)
		ft_putchar_c(n + '0');
	return (count);
}
