#include "../inc/file_to_list.h"

// ONE OF THESE HAS OPTIONAL ARGUMENTS!!!!

int process_ambiant(t_list *current)
{
	int status;
	// printf("\nPROCESS AMBIANT\n");
	// printf("data = %s\n", current->p);

	// alr - 0.0 - 1.0
	status = process_alr(current);
	if (status != E_SUCCESS)
		return (status);
	// rgb - [0-255], [0-255], [0-255]
	status = process_rgb(current);
	if (status != E_SUCCESS)
		return (status);
	// ft_anything_else_in_string_say_no(current->p);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (ret_error(E_EXTRA_CHARS, current));
	// printf("current->p=%s\n", current->p);
	return (E_SUCCESS);
}

int	process_camera(t_list *current)
{
	// printf("\nPROCESS CAMERA\n");
	// printf("data =%s\n", current->p);
	int	status;

	status = 0;
	// xyz - [f], [f], [f]
	status = process_xyz(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));

	// xyz_3d - [-1,1], [-1,1], [-1,1]
	status = process_xyz_3d(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	// fov - [0-180]
	status = process_fov(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));

	// ft_anything_else_in_string_say_no(current->p);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (ret_error(E_EXTRA_CHARS, current));
	return (E_SUCCESS);
}

void process_cylinder(t_list *current)
{
	// printf("\nPROCESS CYLINDER\n");
	// printf("data = %s\n", current->p);

	// xyz - [f], [f], [f]
	process_xyz(current);

	// xyz_3d - [-1,1], [-1,1], [-1,1]
	process_xyz_3d(current);

	// cd - [f]
	process_cd(current);

	// ch - [f]
	process_ch(current);

	// rgb - [0-255], [0-255], [0-255]
	process_rgb(current);

	// ft_anything_else_in_string_say_no(current->p);
}

void process_plane(t_list *current)
{
	// printf("\nPROCESS PLANE\n");
	// printf("data = %s\n", current->p);

	// xyz - [f], [f], [f]
	process_xyz(current);

	// xyz_3d - [-1,1], [-1,1], [-1,1]
	process_xyz_3d(current);

	// rgb - [0-255], [0-255], [0-255]
	process_rgb(current);

	// ft_anything_else_in_string_say_no(current->p);
}

int process_light(t_list *current)
{
	int	status;

	status = 0;
	// printf("\nPROCESS LIGHT\n");
	// printf("data = %s\n", current->p);

	// xyz - [f], [f], [f]
	status = process_xyz(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	// lbr - [0-1]
	status = process_lbr(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));
	// rgb - [0-255], [0-255], [0-255]
	status = process_rgb(current);
	if (status != E_SUCCESS)
		return (ret_error(status, current));

	// ft_anything_else_in_string_say_no(current->p);
	if (current->p[0] != '\0' && current->p[0] != '\n')
		return (ret_error(E_EXTRA_CHARS, current));
	return (E_SUCCESS);
}

void process_sphere(t_list *current)
{
	// printf("\nPROCESS SHPERE\n");
	// printf("data = %s\n", current->p);

	// xyz - [f], [f], [f]
	process_xyz(current);

	// sd - [f]
	process_sd(current);

	// rgb - [0-255], [0-255], [0-255]
	process_rgb(current);

	// ft_anything_else_in_string_say_no(current->p);
}

int	process_node(t_list *current)
{
	if (current->type == ambiant)
	{
		// printf("\n>> we have an ambiant\n");
		if (process_ambiant(current) != E_SUCCESS)
			return(printf(">> !!! Error: ambiant failed  !!! <<\n"));
	}
	else if (current->type == camera)
	{
		// printf("\n>> we have a camera\n");
		if (process_camera(current) != E_SUCCESS)
			return (printf(">> !!! Error: camera failed  !!! <<\n"));
	}
	else if (current->type == light)
	{
		// printf("\n>> we have a light\n");
		if (process_light(current) != E_SUCCESS)
			return (printf(">> !!! Error: Light failed  !!! <<\n"));
	}
	else if (current->type == plane)
	{
		// printf("\n>> we have a plane\n");
		process_plane(current);
	}
	else if (current->type == sphere)
	{
		// printf("\n>> we have a sphere\n");
		process_sphere(current);
	}
	else if (current->type == cylinder)
	{
		// printf("\n>> we have a cylinder\n");
		process_cylinder(current);
	}
	else
	{
		return (printf("\n\n>> Error: has a blank line slipped through??\n\n"));
	}
	return (E_SUCCESS);
}


int	process_nodes(t_list **l)
{
	t_list *current = *l;

	while (current)
	{
		if (process_node(current) != E_SUCCESS)
			return (-1);
		current = current->next;
	}
	return (E_SUCCESS);
}