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

int	allocate_scene_arrays(t_scene *scene)
{
	scene->shape_count = scene->n_sphere + scene->n_plane + scene->n_cylinder;
	if (scene->shape_count > 0)
	{
		scene->shapes = ft_calloc(scene->shape_count, sizeof(t_shape));
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
			scene->shapes[i].xyz.x = current->xyz.x;
			scene->shapes[i].xyz.y = current->xyz.y;
			scene->shapes[i].xyz.z = current->xyz.z;
			scene->shapes[i].xyz.w = POINT;
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
	elem.pos.w = POINT;
	elem.pos.x = current->xyz.x;
	elem.pos.y = current->xyz.y;
	elem.pos.z = current->xyz.z;
	elem.xyz3d = current->xyz_3d;
	elem.focal_length = calculate_focal_len(current->fov);
	return (elem);
}

int	populate_scene(t_list **l, t_scene *scene)
{
	t_list		*current;

	current = *l;
	if (allocate_scene_arrays(scene) == ERROR)
		return (ERROR);
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
			scene->lightpos.w = POINT;
			scene->lightpos.x = current->xyz.x;
			scene->lightpos.y = current->xyz.y;
			scene->lightpos.z = current->xyz.z;
			scene->lbr = current->lbr;
		}
		else if (current->type == camera)
			scene->camera = move_element_into_scene(current);
		current = current->next;
	}
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
	precalculate(scene);
	// ft_list_print(&l);
	ft_lstclear(&l, free);
// free_all(l); // l is a linked list, that holds input data,
	// and rt holds env data?
	return (SUCCESS);
}
