/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:56:36 by jwadding          #+#    #+#             */
/*   Updated: 2024/11/06 00:43:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *s, int *err)
{
	double	divisor;
	double	fraction;
	double	sign;
	double	wholenum;

	divisor = 1.0;
	fraction = 0.0;
	wholenum = 0.0;
	sign = 1;
	if (!s || !*s || !err || *err)
		return (-1);
	if (*s == '-' || *s == '+')
		sign = ',' - *s++;
	wholenum = (double)ft_atoi(s, err);
	while (*s && ft_isdigit(*s))
		s++;
	if (*s && *s++ == '.')
	{
		while (*s && *s >= '0' && *s <= '9')
		{
			divisor *= 10.0;
			fraction += (double)(*s++ - '0') / divisor;
		}
	}
	return (sign * (wholenum + fraction));
}
