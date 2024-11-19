#include "../inc/file_to_list.h"

// int	check_filename(char *filename)
// {
// 	check len.
// 	last three chars == .rt
// }

int	file_to_list(char *filename, t_list **l)
{
	int fd;
	char *line;
	t_list *tmp;
	// tmp = NULL;
	// init_node(&tmp);
	// if(check_filename(filename))
	// 	return(??)

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		// handle blank line. break?
		if ((line[0] == '\n' || line[0] == '\0') && ft_strlen(line) == 1)//is this condition correct?
		{
			free(line);
			//should we assign the line here or loop again?
			line = get_next_line(fd);
		}
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			printf("Error: malloc failed\n");
			return (-1);
		}
		tmp->p = tmp->s;//using p pointer to move through the string so s can be freed later
		ft_lstadd_back(l, tmp);
		line = get_next_line(fd);	
	}
	close(fd);
	return (0);
}

int	allocate_scene_shapes(t_scene *scene)
{
	int shape_count;

	shape_count = scene->n_sphere + scene->n_plane + scene->n_cylinder;
	if (shape_count > 0)
	{
		scene->shapes = ft_calloc(shape_count, sizeof(t_shape));
		if (!scene->shapes)
			return (ERROR);
	}
	return (SUCCESS);
}

void	move_shapes_into_scene(t_list **l, t_scene *scene, enum e_type type)
{
	t_list *current;
	int 	i;

	current = *l;
	//indexing starts from 0 for spheres, then come planes, then cylinders
	i = 0;
	if (type == plane)
		i = scene->n_sphere;
	else if (type == cylinder)
		i = scene->n_sphere + scene->n_plane;
	while (current)
	{
		if (current->type == type)
		{
			scene->shapes[i].type = type;
			scene->shapes[i].xyz = current->xyz;
			scene->shapes[i].xyz3d = current->xyz_3d;
			scene->shapes[i].rgb = current->rgb;
			scene->shapes[i].sd = current->sd;
			scene->shapes[i].cd = current->cd;
			scene->shapes[i].ch = current->ch;
			i++;
		}
		current = current->next;
	}
}

t_elem	move_element_into_scene(t_list *current)
{
	t_elem elem;

	elem.type = current->type;
	elem.rgb = current->rgb;
	elem.xyz = current->xyz;
	elem.xyz3d = current->xyz_3d;
	elem.alr = current->alr;
	elem.lbr = current->lbr;
	elem.focal_length = calculate_focal_len(current->fov);
	return (elem);
}

int	populate_scene(t_list **l, t_scene *scene)
{
	t_list		*current;
	t_colour	*ambiant_tmp;

	current = *l;
	ambiant_tmp = NULL;
	if (allocate_scene_shapes(scene) == ERROR)
		return (ERROR);
	move_shapes_into_scene(l, scene, sphere);
	move_shapes_into_scene(l, scene, plane);
	move_shapes_into_scene(l, scene, cylinder);
	while (current)
	{
		if (current->type == ambiant)
		{
			ambiant_tmp = multiply_colour_by(&current->rgb, current->alr);
			scene->ambiant.r = ambiant_tmp->r;
			scene->ambiant.g = ambiant_tmp->g;
			scene->ambiant.b = ambiant_tmp->b;
		}
		else if (current->type == light)
			scene->light = move_element_into_scene(current);
		else if (current->type == camera)
			scene->camera = move_element_into_scene(current);
		current = current->next;
	}
	free(ambiant_tmp);
	return (SUCCESS);
}

int	parse(int argc, char **argv, t_scene *scene)
{
	t_list	*l;
	//t_scene *scene is for our general program info
	// t_error		exit_code;

	l = NULL;

	if (argc != 2)
		return(ret_error(E_ARGS, NULL));

	if (does_file_end_with_rt(argv[1]) == 0)
		return(ret_error(E_FILE_NAME, NULL));

	if (file_to_list(argv[1], &l))
		return (ret_error(E_MALLOC, l));

	if (process_list(&l) == ERROR)
	{
		printf("======================== FILE VALIDATION FAILED ========================");
		return (-1);
	}
// ft_list_print(&l);
	// assign_scene_object(l);


	if (check_count_of_types(&l, scene) != SUCCESS) // analyse the linked list and store those values in the general program info
		return (ret_error(E_OBJECT_COUNT, l));

	if (populate_scene(&l, scene) != SUCCESS)
		return (ret_error(E_MALLOC, l));
	// init_camera(&rt); 	// camera calculations
	// render_scene(&rt);	// render scene

	// ft_list_print(&l);
	ft_lstclear(&l, free);
// free_all(l); // l is a linked list, that holds input data,
	// and rt holds env data?
	return (SUCCESS);
}
