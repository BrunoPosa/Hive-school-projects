/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:20:48 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/06 14:52:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_select_call(char c, va_list args)
{
	int		count;

	count = 0;
	if (c == 'c')
		count = ft_putchar_c(va_arg(args, int));
	else if (c == 's')
		count = ft_putstr_c(va_arg(args, char *));
	else if (c == 'p')
		count = ft_putptr_c(va_arg(args, unsigned long));
	else if (c == 'd' || c == 'i')
		count = ft_putnbr_c(va_arg(args, int));
	else if (c == 'u')
		count = ft_putunbr_c(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		count = ft_puthex_c(va_arg(args, int), c);
	else if (c == '%')
		count = ft_putchar_c('%');
	else
		count = ft_putchar_c(c);
	return (count);
}

int	ft_printf(const char *input, ...)
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
			count += ft_putchar_c(input[i++]);
		if (input[i] == '%')
		{
			i++;
			count += ft_select_call(input[i++], args);
		}
	}
	va_end(args);
	return (count);
}
