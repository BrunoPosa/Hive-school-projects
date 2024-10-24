/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_two_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:43:56 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

int	get_digit(char c, int digits_in_base)
{
	int	max_digit;

	if (digits_in_base <= 10)
		max_digit = digits_in_base + '0';
	else
		max_digit = digits_in_base - 10 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

char	*strjoin_colors(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		exit(1);
	result = ft_strjoin(temp, s3);
	if (!result)
		exit(1);
	free(temp);
	free(s1);
	free(s2);
	free(s3);
	return (result);
}

float	*conv_color_for(float *a)
{
	float	*r;

	r = color(0, 0, 0);
	if (!r)
		return (NULL);
	r[0] = a[0] / 256;
	r[1] = a[1] / 256;
	r[2] = a[2] / 256;
	return (r);
}

int	*conv_color_back(float *a)
{
	int	*r;

	r = malloc(3 * sizeof(int));
	if (!r)
		return (NULL);
	r[0] = clamp_color(a[0] * 256);
	r[1] = clamp_color(a[1] * 256);
	r[2] = clamp_color(a[2] * 256);
	return (r);
}
