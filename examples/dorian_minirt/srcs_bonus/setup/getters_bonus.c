/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:21:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/28 12:54:39 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "vector_math_bonus.h"

void	ft_skip_ws(char **line)
{
	while (**line == ' ' || **line == '\t')
		*line += 1;
}

void	ft_skip_num(char **line, int mode, int allow_comma)
{
	int	flag;

	flag = 0;
	if (**line == '-' || **line == '+')
		*line += 1;
	while ((ft_isdigit(**line) || (mode != INT && **line == '.' && !flag))
		&& **line != '\0')
	{
		if (**line == '.')
			flag++;
		*line += 1;
	}
	if (ft_isspace(**line) || (**line == ',' && allow_comma))
		return ;
	ft_error(input_err);
}

t_vec4	get_colour(char **line)
{
	int		colour[4];
	t_vec4	res;
	int		i;

	colour[0] = 1;
	i = 1;
	while (i <= 3)
	{
		colour[i] = ft_atoi(*line);
		if (colour[i] < 0 || colour[i] > 255)
			ft_error(range_err);
		if (i == 3)
			break ;
		ft_skip_ws(line);
		while (**line != ',' || **line == '\n' || **line == '\0')
			(*line)++;
		if ((**line != ',') && i < 3)
			ft_error(file_err);
		*line += 1;
		ft_skip_ws(line);
		i++;
	}
	res = ft_trgbtov4(colour);
	ft_rgbtonorm(&res);
	return (res);
}

float	get_float(char **line, int mode)
{
	float	res;

	res = 0;
	res = ft_atof(*line);
	ft_skip_num(line, REAL, FALSE);
	if (mode == RATIO && 0 <= res && res <= 1)
		return (res);
	else if (mode == REAL)
		return (res);
	else if (mode == BALANCE && -1 <= res && res <= 1)
		return (res);
	else if (mode == ANGLE && 0 <= res && res <= 180)
		return (res);
	else
		ft_error(input_err);
	return (FLT_MAX);
}

t_vec3	get_vec3(char **line)
{
	t_vec3	vec;

	ft_skip_ws(line);
	vec.x = ft_atof(*line);
	ft_skip_num(line, REAL, TRUE);
	ft_skip_ws(line);
	if (**line == ',')
		*line += 1;
	ft_skip_ws(line);
	vec.y = ft_atof(*line);
	ft_skip_num(line, REAL, TRUE);
	ft_skip_ws(line);
	if (**line == ',')
		*line += 1;
	ft_skip_ws(line);
	vec.z = ft_atof(*line);
	if (**line == '-')
		*line += 1;
	ft_skip_num(line, REAL, FALSE);
	return (vec);
}
