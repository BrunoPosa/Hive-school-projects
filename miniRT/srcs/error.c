/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:42:47 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 00:16:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "../../libft/libft.h"

static	char	*ft_strerror(t_error error)
{
	if (error == E_SUCCESS)
		return ("Success");
	else if (error == E_ERROR)
		return ("General error");
	else if (error == E_ARGS)
		return ("Invalid arguments");
	else if (error == E_FILE_NAME)
		return ("Invalid filename");
	else if (error == E_ILLEGAL_CHARS1)
		return ("Illegal characters 1");
	else if (error == E_ILLEGAL_CHARS2)
		return ("Illegal characters 2");
	else if (error == E_ILLEGAL_CHARS3)
		return ("Illegal characters 3");
	else if (error == E_ILLEGAL_CHARS4)
		return ("Illegal characters 4");
	else if (error == E_ILLEGAL_CHARS5)
		return ("Illegal characters 5");
	else if (error == E_PROCESS_NODE)
		return ("Process node error");
	else if (error == E_ALR_CHARS)
		return ("ALR character error");
	else if (error == E_ALR_RANGE)
		return ("ALR range error");
	else if (error == E_LBR_CHARS)
		return ("LBR character error");
	else if (error == E_LBR_RANGE)
		return ("LBR range error");
	else if (error == E_XYZ_CHARS)
		return ("XYZ character error");
	else if (error == E_XYZ_COMMA)
		return ("XYZ comma error");
	else if (error == E_FLOAT_CHARS)
		return ("Float character error");
	else if (error == E_UINT_CHARS)
		return ("Unsigned int character error");
	else if (error == E_FOV_RANGE)
		return ("FOV range error");
	else if (error == E_RGB_CHARS)
		return ("RGB character error");
	else if (error == E_RGB_COMMA)
		return ("RGB comma error");
	else if (error == E_RGB_RANGE)
		return ("RGB range error");
	else if (error == E_XYZ_3D_CHARS)
		return ("XYZ 3D character error");
	else if (error == E_XYZ_3D_COMMA)
		return ("XYZ 3D comma error");
	else if (error == E_XYZ_3D_NORMALIZE)
		return ("XYZ 3D normalization error");
	else if (error == E_SPLIT)
		return ("Split error");
	else if (error == E_MALLOC)
		return ("Memory allocation error");
	else if (error == E_GNL)
		return ("malloc() or read() error in GNL\n");
	else if (error == E_WRONG_TYPE)
		return ("Wrong data type");
	else if (error == E_EXTRA_CHARS)
		return ("Extra characters");
	else if (error == E_XYZ_RANGE)
		return ("XYZ range error");
	else if (error == E_OBJECT_COUNT)
		return ("Scene file needs 1 A, 1 C, 1 L, and 1-SHAPE_LIMIT shapes\n");
	else if (error == E_SPHERE_SD)
		return ("Sphere SD error");
	else if (error == E_CYLINDER_CD)
		return ("Cylinder CD error");
	else if (error == E_CYLINDER_CH)
		return ("Cylinder CH error");
	else if (error == E_MLX_INIT)
		return ("MLX initialization error");
	else if (error == E_MLX_IMG)
		return ("MLX image error");
	else if (error == E_MLX_RESIZE)
		return ("MLX resize error");
	else
		return ("Unknown error");
}

/*
	frees what still exists, prints error message if error != 0, returns 'error'.
*/
int	clean_return(t_error error, t_rt *data)
{
	if (data->l)
		ft_lstclear(&data->l, free);
	if (data->scene.shapes)
		free (data->scene.shapes);
	if (data->mlx)
		mlx_terminate(data->mlx);
	data->l = NULL;
	data->scene.shapes = NULL;
	if (error)
	{
		write(2, "Error\n", 6);
		write(2, ft_strerror(error), ft_strlen(ft_strerror(error)));
	}
	return (error);
}
