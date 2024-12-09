/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:38 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 20:46:32 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"


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