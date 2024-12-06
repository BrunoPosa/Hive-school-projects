/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:26:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/12 11:20:51 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
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
		if (((unsigned long long)result > (unsigned long long) LLONG_MIN
				&& sign == -1) || ((sign == 1)
				&& (unsigned long long)result > (unsigned long long) LLONG_MAX))
			return (-1);
	}
	result *= sign;
	return ((long long) result);
}
