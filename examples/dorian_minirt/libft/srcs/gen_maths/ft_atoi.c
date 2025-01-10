/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:26:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/13 07:34:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	sign;
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
		if ((long long)result * sign < (long long)MY_INT_MIN)
			return (0);
		if ((long long)result * sign > (long long)MY_INT_MAX)
			return (-1);
	}
	result *= sign;
	return ((int) result);
}
