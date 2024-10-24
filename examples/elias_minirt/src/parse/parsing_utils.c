/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:13:22 by esalmela          #+#    #+#             */
/*   Updated: 2024/09/27 15:13:24 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_bool	allocate_light(t_parse *parse)
{
	int	i;

	i = -1;
	parse->light = malloc((parse->lightnumb + 1) * (sizeof(t_light *)));
	if (!parse->light && parse->lightnumb > 0)
		return (FALSE);
	parse->light[0] = NULL;
	parse->light[parse->lightnumb] = NULL;
	return (TRUE);
}

static t_bool	fill_rgb2(float **color, float *value, char **rgb, int i)
{
	int	status;

	if (i != 3)
	{
		free_array(rgb);
		free(value);
		return (FALSE);
	}
	free(*color);
	*color = conv_color_for(value);
	free(value);
	status = TRUE;
	if (rgb[i])
		status = FALSE;
	free_array(rgb);
	return (status);
}

t_bool	fill_rgb(float **color, char *str)
{
	int		i;
	char	**rgb;
	float	*value;

	i = -1;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (FALSE);
	value = malloc(3 * sizeof(float));
	if (!value)
	{
		free_array(rgb);
		return (FALSE);
	}
	while (++i <= 2)
	{
		if (!rgb[i] || !ft_isdigit(rgb[i][0]))
			break ;
		value[i] = ft_atoi(rgb[i]);
		if (!(value[i] >= 0 && value[i] <= 255))
			break ;
	}
	return (fill_rgb2(color, value, rgb, i));
}

t_bool	validate_values(char *arg)
{
	int	i;
	int	coma;

	i = 0;
	coma = 0;
	if (!arg)
		return (FALSE);
	while (arg[i])
	{
		if (arg[i] == ',')
		{
			coma++;
			i++;
		}
		if (arg[i] && ((arg[i] != '.' && arg[i] != '-')
				&& (arg[i] < '0' || arg[i] > '9'))
			&& arg[i] != '\n')
			return (FALSE);
		i++;
	}
	if ((!(arg[i - 1] >= '0' && arg[i - 1] <= '9')) && (arg[i - 1] != '\n'))
		return (FALSE);
	if (coma > 2)
		return (FALSE);
	return (TRUE);
}

t_bool	fill_value(char *arg, char **coordinates, float *value)
{
	int	i;

	i = -1;
	if (!arg || arg[0] == '\n')
		return (FALSE);
	if (ft_strlen(arg) > 10)
		return (FALSE);
	while (arg[++i] && arg[i] != '\n')
	{
		if (arg[i] && arg[i] != '.' && arg[i] != '-'
			&& !(arg[i] >= '0' && arg[i] <= '9'))
		{
			if (coordinates)
				free_array(coordinates);
			return (FALSE);
		}
	}
	if (ft_strchr(arg, '.'))
		*value = ft_atof(arg);
	else
		*value = (float)ft_atoi(arg);
	return (TRUE);
}
