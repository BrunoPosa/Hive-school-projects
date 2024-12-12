/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:43:37 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/10 22:07:43 by jwadding         ###   ########.fr       */
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

int	file_to_list(char *filename, t_list **l)
{
	int		fd;
	char	*line;
	t_list	*tmp;

	fd = ft_open(filename);
	line = get_next_line(fd);
	while (line)
	{
		if ((line[0] == '\n' || line[0] == '\0') && ft_strlen(line) == 1)
		{
			free(line);
			line = get_next_line(fd);
		}
		tmp = ft_lstnew(line);
		if (!tmp)
		{
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
	if (allocate_scene_arrays(scene) == E_ERROR)
		return (E_ERROR);
	move_shapes_into_scene(l, scene, sphere);
	move_shapes_into_scene(l, scene, plane);
	move_shapes_into_scene(l, scene, cylinder);
	while (current)
	{
		if (current->type == ambiant)
		{
			scene->ambiant.r = current->rgb.r * current->alr;
			scene->ambiant.g = current->rgb.g * current->alr;
			scene->ambiant.b = current->rgb.b * current->alr;
		}
		else if (current->type == light)
		{
			scene->lightpos.x = current->xyz.x;
			scene->lightpos.y = current->xyz.y;
			scene->lightpos.z = current->xyz.z;
			scene->lbr = current->lbr;
		}
		else if (current->type == camera)
			scene->camera = move_element_into_scene(current);
		current = current->next;
	}
	return (E_SUCCESS);
}

int	import(int argc, char **argv, t_scene *scene)
{
	t_list	*l;

	l = NULL;
	if (argc != 2)
		return (ret_error(E_ARGS, NULL));
	if (does_file_end_with_rt(argv[1]) == 0)
		return (ret_error(E_FILE_NAME, NULL));
	if (file_to_list(argv[1], &l))
		return (ret_error(E_MALLOC, l));
	if (process_list(&l) == E_ERROR)
	{
		printf("==== FILE VALIDATION FAILED ====");
		return (-1);
	}
	if (check_count_of_types(&l, scene) != E_SUCCESS)
		return (ret_error(E_OBJECT_COUNT, l));
	if (populate_scene(&l, scene) != E_SUCCESS)
		return (ret_error(E_MALLOC, l));
	precalculate(scene);
	ft_lstclear(&l, free);
	return (E_SUCCESS);
}
