/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:43:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/22 04:12:36 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

static	int	ft_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		//use error function
		return (-1);
	}
	return (fd);
}
// check condition "if ((line[0] == '\n' || line[0] == ..."
//using p pointer to move through the string so s can be freed later
/*
*	reads the file and creates a linked list of strings
*/
int	file_to_list(char *filename, t_list **l)
{
	int		fd;
	char	*line;
	t_list	*tmp;

	fd = ft_open(filename);
	line = get_next_line(fd);
	while (line)
	{
/*
 is this the point where we can say line[0] == '#' then we skip.
 Why do we have a line length == 1 check?
 Perhaps this is irelevant if the line did start with /n, /0 or #.
*/
		if ((line[0] == '\n' || line[0] == '\0') && ft_strlen(line) == 1)
		{
			free(line);
			line = get_next_line(fd);
		}
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			// transform to enum system
			printf("Error: malloc failed\n");
			return (-1);
		}
		tmp->p = tmp->s;
		ft_lstadd_back(l, tmp);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
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
{
	t_list	*l;
	int		status;

	status = 0;
	l = NULL;
	
	/*
		Build new function: ft_file_checks

		The purose is to handle any time of file checking that needs to be done before the file is read.
		
		This ft would need to take in: 
			argc
			argv[1]

		It would need to return an int error code

		It would remove the next four lines of code.
	*/
	
	if (argc != 2)
		return (ret_error(E_ARGS, NULL));
		
	if (does_file_end_with_rt(argv[1]) == 0)
		return (ret_error(E_FILE_NAME, NULL));

// put each line of the file into a linked list. Skip the line if it is blank or starts with a #
		
	status = file_to_list(argv[1], &l);
	if (status != E_SUCCESS)  // we might drop all this '!=' because we might learn what if(status) or if(!status) means
		return (status);

// turn the list of rows into seperated values		
	status = process_list(&l);
	if (status != E_SUCCESS)
	{
		printf("==== FILE VALIDATION FAILED ====\nerrno: %d\n", status);
		return (status);
	}


// check we have our trousers on
	if (check_count_of_types(&l, scene) != E_SUCCESS)
		return (ret_error(E_OBJECT_COUNT, l));

// this is three lines that assign macros to values in the scene - abstract this into a function
	scene->window.w = WINSIZE;
	scene->window.h = WINSIZE;
	scene->aspect_r = scene->window.w / scene->window.h;

// bruno turns up to the party and takes our struct into what he needs?
	if (populate_scene(&l, scene) != E_SUCCESS)
		return (ret_error(E_MALLOC, l));

// bruno says he's done and leaves the party
	ft_lstclear(&l, free);
	return (E_SUCCESS);
}
