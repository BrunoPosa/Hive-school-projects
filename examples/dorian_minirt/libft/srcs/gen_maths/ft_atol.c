/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:26:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/12 10:00:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == ' ' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\n' || str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while ('0' <= str[i] && str[i] <= '9' && str[i] != '\0')
	{	
		result = (result * 10) + (str[i++] - '0');
		if ((long long)result * sign < (long long)LONG_MIN)
			return (0);
		if ((long long)result * sign > (long long)LONG_MAX)
			return (-1);
	}
	result *= sign;
	return ((long) result);
}
