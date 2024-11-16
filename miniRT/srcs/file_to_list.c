#include "../inc/file_to_list.h"
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
		ft_lstadd_back(l, tmp);
		line = get_next_line(fd);	
	}
	close(fd);
	return (0);
}

int	populate_scene(t_list **l, t_scene *scene)
{
	t_list *current;

	current = *l;
	while (current)
	{
		if (current->type == ambiant)
			scene->ambiant = current;
		else if (current->type == light)
			scene->light = current;
		else if (current->type == camera)
			scene->camera = current;
		else
			printf("parsing sp, pl, cy into t_rt scene struct not yet implemented\n");
		current = current->next;
	}
	return (SUCCESS);
}

int	parse(int argc, char **argv, t_scene *scene)
{
	t_list	*l;
	//t_scene *scene this is for our general program info
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
	// assign_scene_object(l);

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (ret_error(E_MALLOC, l));

	if (check_count_of_types(&l, scene) != SUCCESS) // analyse the linked list and store those values in the general program info
		return (ret_error(E_OBJECT_COUNT, l));
	
	if (populate_scene(&l, scene) != SUCCESS)
		return (ret_error(E_MALLOC, l));
	// init_camera(&rt); 	// camera calculations
	// render_scene(&rt);	// render scene

	// ft_list_print(&l);
	// free_all(&l); // l is a linked list, that holds input data,
	// and rt holds env data?
	return (SUCCESS);
}
