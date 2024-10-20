/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:03:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 13:54:06 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

unsigned int	ft_atoi_base(const char *str, int str_base)
{
	unsigned int	result;
	int				digit;

	result = 0;
	digit = get_digit(to_lower(*str), str_base);
	while (digit >= 0)
	{
		result = result * str_base;
		result = result + digit;
		++str;
		digit = get_digit(to_lower(*str), str_base);
	}
	return (result);
}

unsigned int	ft_atoi_baseintense(const char *str, int str_base)
{
	unsigned int	result;
	int				digit;

	result = 0;
	digit = get_digit(to_lower(*str), str_base);
	while (digit >= 0)
	{
		result = result * str_base;
		result = result + digit;
		++str;
		digit = get_digit(to_lower(*str), str_base);
	}
	result = result * str_base;
	result = result + 15;
	result = result * str_base;
	result = result + 15;
	return (result);
}

char	*int_to_hex(int num)
{
	char	*hexstr;
	char	*hexchars;

	hexstr = malloc(3 * sizeof(char));
	if (!hexstr)
		return (NULL);
	hexchars = "0123456789ABCDEF";
	hexstr[0] = hexchars[(num >> 4) & 0xF];
	hexstr[1] = hexchars[num & 0xF];
	hexstr[2] = '\0';
	return (hexstr);
}

int	colors_to_int(int *colors, int intensity)
{
	char	*string;
	int		result;
	char	*temp;
	char	*intens;

	string = strjoin_colors(int_to_hex(colors[0]), int_to_hex(colors[1]),
			int_to_hex(colors[2]));
	if (intensity == 256)
		result = ft_atoi_baseintense(string, 16);
	else
	{
		intens = int_to_hex(intensity);
		temp = ft_strjoin(string, intens);
		free(intens);
		result = ft_atoi_base(temp, 16);
		free(temp);
	}
	free(string);
	return (result);
}

float	clamp_color(float n)
{
	if (n > 255)
		return (255);
	return (n);
}
