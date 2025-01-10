/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:40:37 by esalmela          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt_bonus.h"

static	char	*get_shape(t_object *object)
{
	char	*shape;

	if (object->s == SPHERE)
		shape = "sphere";
	else if (object->s == PLANE)
		shape = "plane";
	else if (object->s == CYLINDER)
		shape = "cylinder";
	else
		shape = "cone";
	return (shape);
}

void	free_objects_exit(t_object **object, char **args,
int amount, t_parse *p)
{
	int		i;
	char	*msg;
	char	*shape;

	msg = "In parsing object";
	shape = get_shape(object[amount]);
	i = -1;
	if (args)
		free_array(args);
	if (p)
		clean_parse(p);
	while (++i <= amount)
	{
		if (object[i]->material->pattern == TRUE)
			free(object[i]->material->color);
		clean_object(object[i]);
	}
	free(object);
	ft_printf(2, "Error\n%s %s\n", msg, shape);
	exit(1);
}

void	free_array(char **args)
{
	int	i;

	i = -1;
	if (!args)
		return ;
	while (args[++i])
		free(args[i]);
	free(args);
}

void	exit_error(char *msg, char **args, t_parse *parse)
{
	if (parse)
		clean_parse(parse);
	if (args)
		free_array(args);
	ft_printf(2, "Error\n%s\n", msg);
	exit(1);
}
