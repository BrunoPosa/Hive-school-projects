/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extra_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:33:41 by esalmela          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

t_bool	check_pattern(t_object **object, int index, char **args, int n)
{
	if (args[n])
	{
		if (!ft_strncmp(args[n], "P\n", 3) || !ft_strncmp(args[n], "P", 2))
		{
			object[index]->material->pattern = TRUE;
			return (TRUE);
		}
		else if (!ft_strncmp(args[n], "B\n", 3) || !ft_strncmp(args[n], "B", 2))
		{
			object[index]->bump = TRUE;
			return (TRUE);
		}
		return (FALSE);
	}
	return (TRUE);
}

t_bool	parse_cone2(char **args, t_object **object, int index, char **values)
{
	int	i;

	i = -1;
	while (++i <= 2)
	{
		if (!fill_value(values[i], values, &object[index]->normv[i]))
			break ;
		if (!(object[index]->normv[i] >= -1.0
				&& object[index]->normv[i] <= 1.0))
			break ;
	}
	free_array(values);
	if (i != 3)
		return (FALSE);
	if (equal_float(magnitude(object[index]->normv), 1) == 0
		|| !fill_value(args[3], NULL, &object[index]->diameter)
		|| object[index]->diameter <= 0.0
		|| !fill_value(args[4], NULL, &object[index]->height)
		|| object[index]->height <= 0.0 || !validate_values(args[5])
		|| !fill_rgb(&object[index]->material->color, args[5]))
		return (FALSE);
	object[index]->cylindermax = object[index]->height;
	return (check_pattern(object, index, args, 6));
}

t_bool	parse_cone(char **args, int index, t_object **object, t_parse *parse)
{
	char	**values;
	int		i;

	object[index] = create_object(CONE, parse);
	if (!validate_values(args[1]))
		return (FALSE);
	i = -1;
	values = ft_split(args[1], ',');
	if (!values)
		return (FALSE);
	while (++i <= 2)
		if (!fill_value(values[i], values, &object[index]->coord[i]))
			break ;
	free_array(values);
	if (i != 3)
		return (FALSE);
	if (!validate_values(args[2]))
		return (FALSE);
	values = ft_split(args[2], ',');
	if (!values)
		return (FALSE);
	return (parse_cone2(args, object, index, values));
}

t_bool	validate_light2(char **args, t_parse *parse, int index, t_light *light)
{	
	if (args[3])
	{
		if (!validate_values(args[3]))
			return (FALSE);
		if (!fill_rgb(&light->color, args[3]))
			return (FALSE);
	}
	parse->light[index]->color = multiply_color(light->color,
			parse->lbrightness, 1);
	if (args[3] && args[4])
		return (FALSE);
	return (TRUE);
}

t_bool	validate_light(char **args, t_parse *parse, int index)
{
	char		**coordinates;
	int			i;
	t_light		*light;

	light = create_light();
	parse->light[index] = light;
	if (!light)
		return (FALSE);
	i = -1;
	coordinates = ft_split(args[1], ',');
	if (!coordinates)
		return (FALSE);
	while (++i <= 2)
		if (!fill_value(coordinates[i], coordinates,
				&parse->light[index]->coord[i]))
			break ;
	free_array(coordinates);
	if (i != 3)
		return (FALSE);
	if (!fill_value(args[2], NULL, &parse->lbrightness))
		return (FALSE);
	if (!(parse->lbrightness >= 0.0 && parse->lbrightness <= 1.0))
		exit_error("Invalid light brightness value", args, parse);
	return (validate_light2(args, parse, index, light));
}
