/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:43:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 03:36:31 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	allocate_shape_array(t_scene *scene)
{
	scene->shape_count = scene->n_sphere + scene->n_plane + scene->n_cylinder;
	if (scene->shape_count > 0)
	{
		scene->shapes = ft_calloc(scene->shape_count, sizeof(t_shape));
		if (!scene->shapes)
			return (E_MALLOC);
	}
	return (E_SUCCESS);
}

static int	add_line_to_node_to_list(t_list **l, char *line, int *error)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node)
	{
		*error = E_MALLOC;
		return (E_MALLOC);
	}
	node->p = node->s;
	ft_lstadd_back(l, node);
	node = NULL;
	return (E_SUCCESS);
}

/*
*	Opens, reads, and closes the file, allocating nodes into 'l', each holding a
*	malloc'd string 's' (the line returned by get-next-line). Returns error code
*	on error, freeing the line; saves close(fd) return value to *fd_close_check.
*/
int	file_to_list(char *filename, t_list **l, int *fd_close_check)
{
	char	*line;
	int		error;
	int		fd;

	line = NULL;
	error = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free_return(line, E_OPEN_CLOSE_ERROR));
	line = get_next_line(fd, &error);
	while (line && error != -1 && error != E_MALLOC)
	{
		if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			line = get_next_line(fd, &error);
			continue ;
		}
		if (add_line_to_node_to_list(l, line, &error))
			break ;
		line = get_next_line(fd, &error);
	}
	*fd_close_check = close(fd);
	return (free_return(line, error));
}

int	populate_scene(t_list **l, t_scene *scene)
{
	t_list		*current;

	current = *l;
	if (allocate_shape_array(scene))
		return (E_MALLOC);
	scene->window.w = WINSIZE;
	scene->window.h = WINSIZE;
	scene->aspect_r = scene->window.w / scene->window.h;
	move_shapes_into_scene(l, scene, sphere);
	move_shapes_into_scene(l, scene, plane);
	move_shapes_into_scene(l, scene, cylinder);
	while (current)
	{
		if (current->type == ambiant)
			scene->ambiant = scale_colour(current->rgb, current->alr);
		else if (current->type == light)
		{
			scene->lightxyz = current->xyz;
			scene->lbr = current->lbr;
		}
		else if (current->type == camera)
			scene->cam = move_cam_into_scene(current);
		current = current->next;
	}
	return (E_SUCCESS);
}

int	import(int argc, char **argv, t_rt *data)
{
	int	status;
	int	fd_close_check;

	status = 0;
	fd_close_check = 0;
	if (argc != 2)
		return (E_ARGS);
	if (!does_file_end_with_rt(argv[1]))
		return (E_FILE_NAME);
	status = file_to_list(argv[1], &data->l, &fd_close_check);
	if (status || fd_close_check)
	{
		if (status == -1)
			return (E_GNL);
		else if (fd_close_check)
			return (E_OPEN_CLOSE_ERROR);
		else
			return (status);
	}
	status = process_list(&data->l);
	if (status)
		return (status);
	if (check_count_of_types(&data->l, &data->scene))
		return (E_OBJECT_COUNT);
	return (populate_scene(&data->l, &data->scene));
}
