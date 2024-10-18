/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:33:43 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/08/27 13:33:45 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/utils.h"

/* size of double string */
int	doublelen(char **str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

/* 
checking is number of elements correct 
return 0 if fails, 1 if pass
*/
int	numofel(char **str, int n)
{
	if (doublelen(str) != n)
	{
		error_msg("incorrect number of elements in a line!\n", 0);
		return (0);
	}
	return (1);
}

/* freeing array of strings */
void	free_arr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	is_float(char *str)
{
	int	i;
	int	is_dot;

	i = 0;
	is_dot = 0;
	if (!str || !str[i])
		return (0);
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1 && str[i] != '.')
			return (0);
		if (str[i] == '.' && is_dot != 0)
			return (0);
		if (str[i] == '.')
			is_dot = 1;
		i++;
	}
	return (1);
}

/* 
atoi for float 
*/
float	ft_atof(char *str)
{
	float	sum;
	float	prec;
	float	div;
	float	sign;

	prec = 0.0;
	div = 1.0;
	sign = 1.0;
	if (str && str[0] == '-')
		sign *= -1.0;
	sum = (float)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			div *= 10.0;
			prec += (*str - '0') / div;
			str++;
		}
		sum += prec * sign;
	}
	return (sum);
}
