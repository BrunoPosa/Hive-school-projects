/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:20:48 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/06 14:52:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_select_call(char c, int fd, va_list args)
{
	int		count;

	count = 0;
	if (c == 'c')
		count = ft_putchar_c2(va_arg(args, int), fd);
	else if (c == 's')
		count = ft_putstr_c2(va_arg(args, char *), fd);
	else if (c == 'p')
		count = ft_putptr_c2(va_arg(args, unsigned long), fd);
	else if (c == 'd' || c == 'i')
		count = ft_putnbr_c2(va_arg(args, int), fd);
	else if (c == 'u')
		count = ft_putunbr_c2(va_arg(args, unsigned int), fd);
	else if (c == 'x' || c == 'X')
		count = ft_puthex_c2(va_arg(args, int), c, fd);
	else if (c == '%')
		count = ft_putchar_c2('%', fd);
	else
		count = ft_putchar_c2(c, fd);
	return (count);
}

int	ft_printf_fd(int fd, const char *input, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (!input || input[0] == '\0')
		return (0);
	i = 0;
	count = 0;
	va_start(args, input);
	while (input[i])
	{
		while (input[i] != '%' && input[i])
			count += ft_putchar_c2(input[i++], fd);
		if (input[i] == '%')
		{
			i++;
			count += ft_select_call(input[i++], fd, args);
		}
	}
	va_end(args);
	return (count);
}
