/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:32:39 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/02 15:10:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (!n)
		return ;
	if (n == MY_INT_MIN)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -1 * n;
	}
	if (n > 9)
	{
		ft_putnbr(n * 0.1);
		n %= 10;
	}
	if (n <= 9)
		ft_putchar(n + '0');
}
