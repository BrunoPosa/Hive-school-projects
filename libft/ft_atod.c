/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:56:36 by jwadding          #+#    #+#             */
/*   Updated: 2024/11/03 17:42:18 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *s, int *err)
{
	double	divisor;
	double	fraction;
	double	wholenum;

	divisor = 1.0;
	fraction = 0.0;
	wholenum = (double)ft_atoi(s, err);
	if (!s || !*s || !err || *err)
		return (-1);
	if (*s == '-' || *s == '+')
		s++;
	while (*s && ft_isdigit(*s))
		s++;
	if (s && *s++ == '.')
	{
		while (s && *s && *s >= '0' && *s <= '9')
		{
			divisor *= 10.0;
			fraction = fraction + (double)(*s - '0') / divisor;
			s++;
		}
	}
	if (wholenum < 0)
		return (wholenum - fraction);
	return (wholenum + fraction);
}
