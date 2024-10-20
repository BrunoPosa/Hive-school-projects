/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filehandler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:04:31 by esalmela          #+#    #+#             */
/*   Updated: 2024/09/27 16:37:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

static void	recon_object(char **args, t_object **object, t_parse *parse)
{
	static int	i;

	if (!ft_strncmp(args[0], "sp", ft_strlen(args[0])))
	{
		if (!parse_sphere(args, i, object, parse))
			free_objects_exit(object, args, i, parse);
	}
	else if (!ft_strncmp(args[0], "pl", ft_strlen(args[0])))
	{
		if (!parse_plane(args, i, object, parse))
			free_objects_exit(object, args, i, parse);
	}
	else if (!ft_strncmp(args[0], "cy", ft_strlen(args[0])))
	{
		if (!parse_cylinder(args, i, object, parse))
			free_objects_exit(object, args, i, parse);
	}
	else if (!ft_strncmp(args[0], "co", ft_strlen(args[0])))
	{
		if (!parse_cone(args, i, object, parse))
			free_objects_exit(object, args, i, parse);
	}
	else
		return ;
	i++;
}

static	t_object	**read_objects(int fd, t_parse *parse)
{
	char		*line;
	char		**args;
	t_object	**object;

	line = get_next_line(fd);
	object = malloc(parse->total * sizeof(t_object *));
	if (!object && parse->total > 0)
		exit_error("Malloc", NULL, parse);
	while (line)
	{
		args = ft_split(line, ' ');
		free (line);
		if (!args)
			exit_error("Malloc", NULL, parse);
		recon_object(args, object, parse);
		free_array(args);
		line = get_next_line(fd);
	}
	return (object);
}

static void	count_objects(char **args, t_parse *parse)
{
	if (!ft_strncmp(args[0], "sp", 3))
		parse->total++;
	if (!ft_strncmp(args[0], "pl", 3))
		parse->total++;
	if (!ft_strncmp(args[0], "cy", 3))
		parse->total++;
	if (!ft_strncmp(args[0], "co", 3))
		parse->total++;
	if (!ft_strncmp(args[0], "L", 3))
		parse->lightnumb++;
	if (!ft_strncmp(args[0], "A", 2))
		parse->amnum++;
	if (!ft_strncmp(args[0], "C", 2))
		parse->cnum++;
}

static void	read_file(int fd, t_parse *parse, t_bool flag)
{
	char	*line;
	char	**args;

	line = get_next_line(fd);
	while (flag == FALSE && line)
	{
		args = ft_split(line, ' ');
		free(line);
		count_objects(args, parse);
		free_array(args);
		line = get_next_line(fd);
	}
	if (parse->amnum != 1 || parse->cnum != 1)
		exit_error("Invalid number for ambient or camera", NULL, parse);
	while (flag == TRUE && line)
	{
		args = ft_split(line, ' ');
		free(line);
		if (!args || validate_line(args, parse) != TRUE)
			exit_error("Parsing elements", args, parse);
		free_array(args);
		line = get_next_line(fd);
	}
	close(fd);
}

t_object	**check_file(char *file, t_parse *parse, int flag)
{
	int			len;
	int			fd;
	t_object	**object;

	len = ft_strlen(file);
	if (ft_strncmp(file + (len - 3), ".rt", 3) != 0)
		exit_error("File must be in format .rt", NULL, parse);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Failed to open file", NULL, parse);
	if (flag == FALSE)
	{
		read_file(fd, parse, FALSE);
		return (check_file(file, parse, TRUE));
	}
	else if (flag == TRUE)
	{
		if (!allocate_light(parse))
			exit_error("Malloc", NULL, parse);
		read_file(fd, parse, TRUE);
		return (check_file(file, parse, 2));
	}
	object = read_objects(fd, parse);
	return (object);
}
