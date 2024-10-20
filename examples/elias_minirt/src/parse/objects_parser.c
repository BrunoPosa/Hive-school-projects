/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:04:45 by esalmela          #+#    #+#             */
/*   Updated: 2024/09/16 16:04:46 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_bool	parse_cylinder2(char **args, t_object **object,
	int index, char **values)
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
	object[index]->cylindermax = (object[index]->height / 2);
	object[index]->cylindermin = -(object[index]->height / 2);
	return (check_pattern(object, index, args, 6));
}

t_bool	parse_cylinder(char **args, int index,
t_object **object, t_parse *parse)
{
	char	**values;
	int		i;

	object[index] = create_object(CYLINDER, parse);
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
	return (parse_cylinder2(args, object, index, values));
}

t_bool	parse_plane2(char **args, t_object **object, int index, char **values)
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
	if (equal_float(magnitude(object[index]->normv), 1) == 0)
		return (FALSE);
	if (!validate_values(args[3]))
		return (FALSE);
	if (!fill_rgb(&object[index]->material->color, args[3]))
		return (FALSE);
	return (check_pattern(object, index, args, 4));
}

t_bool	parse_plane(char **args, int index, t_object **object, t_parse *parse)
{
	char	**values;
	int		i;

	object[index] = create_object(PLANE, parse);
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
	i = -1;
	if (!validate_values(args[2]))
		return (FALSE);
	values = ft_split(args[2], ',');
	if (!values)
		return (FALSE);
	return (parse_plane2(args, object, index, values));
}

t_bool	parse_sphere(char **args, int index, t_object **object, t_parse *parse)
{
	char	**values;
	int		i;

	object[index] = create_object(SPHERE, parse);
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
	if (!fill_value(args[2], NULL, &object[index]->diameter)
		|| !validate_values(args[3])
		|| !fill_rgb(&object[index]->material->color, args[3]))
		return (FALSE);
	return (check_pattern(object, index, args, 4));
}
