/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectobase_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:49:23 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/26 13:57:33 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dectobase_str(int n, int base)
{
	char	*num;
	size_t	i;
	int		remainder;
	int		quotient;

	i = 0;
	num = (char *)malloc(sizeof(char) * ft_lenbase(n, base) + 1);
	if (!num)
		return (NULL);
	quotient = n;
	while (quotient)
	{
		remainder = quotient % base;
		if (remainder <= 9)
			num[i++] = remainder + '0';
		else
			num[i++] = (remainder % 10) + 'A';
		quotient /= base;
	}
	num[i] = '\0';
	ft_strrev(num);
	return (num);
}
