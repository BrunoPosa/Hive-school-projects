/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:22:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/08 15:44:30 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	size_t	i;
	char	tmp;
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len-- < 2)
		return ;
	i = 0;
	while (i < len)
	{
		tmp = str[i];
		str[i++] = str[len];
		str[len--] = tmp;
	}
}

int	return_null(void)
{
	ft_putstr_c("(null)");
	return (6);
}

size_t	ft_len16(unsigned long long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

char	*ft_dec_hexstr(unsigned long n)
{
	char			*hex;
	size_t			i;
	unsigned long	remainder;
	unsigned long	quotient;

	i = 0;
	if (!n)
		return (NULL);
	hex = (char *)malloc(sizeof(char) * (ft_len16(n) + 1));
	if (!hex)
		return (NULL);
	quotient = n;
	while (quotient)
	{
		remainder = quotient % 16;
		if (remainder <= 9)
			hex[i++] = remainder + '0';
		else
			hex[i++] = (remainder % 10) + 'A';
		quotient /= 16;
	}
	hex[i] = '\0';
	ft_strrev(hex);
	return (hex);
}
