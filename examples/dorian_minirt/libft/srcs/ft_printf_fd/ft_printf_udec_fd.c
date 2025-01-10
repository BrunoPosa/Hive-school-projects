/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_udec_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:26:39 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/02 15:10:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr_c2(unsigned int n, int fd)
{
	int		count;

	count = 0;
	if (n > 9)
	{
		count += ft_putnbr_c2(n * 0.1, fd);
		n %= 10;
	}
	if (n <= 9)
		count += ft_putchar_c2(n + '0', fd);
	return (count);
}
