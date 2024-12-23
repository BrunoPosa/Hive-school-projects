/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:43:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 04:04:15 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
*	reads the file and creates a linked list of strings
*/
int	file_to_list(char *filename, t_list **l)
{
	int		fd;
	char	*line;
	t_list	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return(E_OPEN_CLOSE_ERROR);
	line = get_next_line(fd);
	while (line)
	{
		if ((line[0] == '\n' || line[0] == '\0'|| line[0] == '#')) // && ft_strlen(line) == 1)
		{
			free(line);
			line = get_next_line(fd);
		}
		tmp = ft_lstnew(line);
		if (!tmp)
			return (E_MALLOC);
		tmp->p = tmp->s;
		ft_lstadd_back(l, tmp);
		line = get_next_line(fd);
	}
	if (close(fd))
		return (E_OPEN_CLOSE_ERROR);
	return (E_SUCCESS);
}

int	populate_scene(t_list **l, t_scene *scene)
{
	t_list		*current;

	current = *l;
	if (allocate_scene_arrays(scene) != E_SUCCESS)
		return (E_MALLOC);
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

int	import(int argc, char **argv, t_scene *scene)
// int	import(int argc, char **argv, t_rt *data)
{
// make this t_list start from main, in the struct
	t_list	*l;
	int		status;

	status = 0;
	l = NULL;	
	if (argc != 2)
		return (E_ARGS);
	if (!does_file_end_with_rt(argv[1]))
		return (E_FILE_NAME);	
	status = file_to_list(argv[1], &l);
	if (status) 
		return (status);	
	status = process_list(&l);
	if (status)
		return (status);

// start of old code
	if (check_count_of_types(&l, scene))
		return (E_OBJECT_COUNT);
	scene->window.w = WINSIZE;
	scene->window.h = WINSIZE;
	scene->aspect_r = scene->window.w / scene->window.h;
	if (populate_scene(&l, scene))
		return (E_MALLOC);
// end of old code


// start of new proposal
	// if (check_count_of_types(&l, data->scene))
	// 	return (E_OBJECT_COUNT);
	// data->scene->window.w = WINSIZE;
	// data->scene->window.h = WINSIZE;
	// data->scene->aspect_r = data->scene->window.w / data->scene->window.h;
	// if (populate_scene(&l, data->scene))
	// 	return (E_MALLOC);
// end of new proposal

	ft_lstclear(&l, free);
	return (E_SUCCESS);
}
