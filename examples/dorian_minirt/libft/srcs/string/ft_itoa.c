/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:11:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/02 15:10:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digits(int n)
{
	size_t	log;

	log = 0;
	if (n == 0)
	{
		log = 1;
	}
	else
	{	
		while (n != 0)
		{
			n /= 10;
			log++;
		}
	}
	return (log);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		len;
	long		num;

	num = n;
	len = ft_digits(n);
	if (n < 0)
	{
		num *= -1;
		len++;
	}
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len) = 0;
	while (len--)
	{
		*(str + len) = num % 10 + '0';
		num = num * 0.1;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}
