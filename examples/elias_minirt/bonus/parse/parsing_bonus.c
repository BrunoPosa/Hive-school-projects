/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:22:55 by esalmela          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

t_bool	validate_ambient(char **args, t_parse *parse)
{
	float	lightratio;

	if (!args[1])
		return (FALSE);
	if (!validate_values(args[1]))
		exit_error("invalid format", args, parse);
	lightratio = ft_atof(args[1]);
	if (lightratio < 0.0 || lightratio > 1.0
		|| (lightratio == 0.0 && args[1][0] != '0'))
		return (FALSE);
	parse->alightr = lightratio;
	if (!validate_values(args[2]))
		return (FALSE);
	if (!fill_rgb(&parse->amcolor, args[2]))
		return (FALSE);
	parse->amcolor = multiply_color(parse->amcolor, parse->alightr, 1);
	if (args[3])
		return (FALSE);
	return (TRUE);
}

static t_bool	validate_camera2(t_parse *parse, char **args)
{
	char	**coordinates;
	int		i;

	i = -1;
	coordinates = ft_split(args[2], ',');
	if (!coordinates)
		return (FALSE);
	while (++i <= 2)
		if (!fill_value(coordinates[i], coordinates, &parse->normv[i]))
			break ;
	free_array(coordinates);
	if (i != 3)
		return (FALSE);
	if (args[3])
		parse->fow = ft_atoi(args[3]);
	else
		return (FALSE);
	if (!ft_isdigit(args[3][0]) && args[3][0] != '0')
		exit_error("invalid fow format", args, parse);
	if (parse->fow < 0 || parse->fow > 180)
		exit_error("invalid fow format", args, parse);
	return (TRUE);
}

t_bool	validate_camera(char **args, t_parse *parse)
{
	int		i;
	char	**coordinates;

	i = -1;
	if (!validate_values(args[1]))
		return (FALSE);
	coordinates = ft_split(args[1], ',');
	if (!coordinates)
		return (FALSE);
	while (++i <= 2)
		if (!fill_value(coordinates[i], coordinates, &parse->camc[i]))
			break ;
	free_array(coordinates);
	if (i != 3)
		return (FALSE);
	i = -1;
	if (!validate_values(args[2]))
		return (FALSE);
	return (validate_camera2(parse, args));
}

t_bool	validate_line(char **args, t_parse *parse)
{
	static int	index;

	if (!ft_strncmp(args[0], "A", 2))
		return (validate_ambient(args, parse));
	else if (!ft_strncmp(args[0], "C", 2))
		return (validate_camera(args, parse));
	else if (!ft_strncmp(args[0], "L", 2))
	{
		index++;
		return (validate_light(args, parse, index - 1));
	}
	else if (!ft_strncmp(args[0], "sp", 3)
		|| !ft_strncmp(args[0], "pl", 3)
		|| !ft_strncmp(args[0], "cy", 3)
		|| !ft_strncmp(args[0], "co", 3)
		|| !ft_strncmp(args[0], "\n", 2))
		return (TRUE);
	else
		return (FALSE);
	return (TRUE);
}
