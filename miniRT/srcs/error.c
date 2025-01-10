/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:42:47 by jwadding          #+#    #+#             */
/*   Updated: 2025/01/09 13:54:07 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static char	*ft_strerror_last(t_error error)
{
	if (error == E_OPEN_CLOSE_ERROR)
		return ("Open or Close error\n");
	else if (error == E_ILLEGAL_CHARS_GENERAL)
		return ("Illegal chars found; use only 0123456789.CALplcysp -,\\n\n\n");
	else if (error == E_MLX_RESIZE)
		return ("MLX failed to resize\n");
	else if (error == E_SHAPE_LIMIT)
		return ("There should be 1-150 shapes in scene file\n");
	else
		return ("Unknown error\n");
}

static char	*ft_strerror_next_next(t_error error)
{
	if (error == E_SPLIT)
		return ("Split error\n");
	else if (error == E_MALLOC)
		return ("Memory allocation error\n");
	else if (error == E_GNL)
		return ("malloc() or read() error in GNL\n");
	else if (error == E_WRONG_TYPE)
		return ("Wrong data type\n");
	else if (error == E_EXTRA_CHARS)
		return ("Extra characters\n");
	else if (error == E_XYZ_RANGE)
		return ("XYZ range error\n");
	else if (error == E_OBJECT_COUNT)
		return ("Scene file needs 1 element (1xA, 1xC, 1xL, and <150 shapes)\n");
	else if (error == E_SPHERE_SD)
		return ("Sphere SD error\n");
	else if (error == E_CYLINDER_CD)
		return ("Cylinder CD error\n");
	else if (error == E_CYLINDER_CH)
		return ("Cylinder CH error\n");
	else if (error == E_MLX_INIT)
		return ("MLX initialization error\n");
	else if (error == E_MLX_IMG)
		return ("MLX image error\n");
	return (ft_strerror_last(error));
}

static char	*ft_strerror_next(t_error error)
{
	if (error == E_LBR_RANGE)
		return ("LBR range error\n");
	else if (error == E_XYZ_CHARS)
		return ("XYZ character error\n");
	else if (error == E_XYZ_COMMA)
		return ("XYZ comma error\n");
	else if (error == E_FLOAT_CHARS)
		return ("Float character error\n");
	else if (error == E_UINT_CHARS)
		return ("Illegal chars found in one of rgb/fov values; use only 0-9\n");
	else if (error == E_FOV_RANGE)
		return ("FOV range error\n");
	else if (error == E_RGB_CHARS)
		return ("RGB character error\n");
	else if (error == E_RGB_COMMA)
		return ("RGB comma error\n");
	else if (error == E_RGB_RANGE)
		return ("RGB range error\n");
	else if (error == E_XYZ_3D_CHARS)
		return ("XYZ 3D character error\n");
	else if (error == E_XYZ_3D_COMMA)
		return ("XYZ 3D comma error\n");
	else if (error == E_XYZ_3D_NORMALIZE)
		return ("XYZ 3D normalization error\n");
	return (ft_strerror_next_next(error));
}

static char	*ft_strerror(t_error error)
{
	if (error == E_ERROR)
		return ("General error\n");
	else if (error == E_ARGS)
		return ("Invalid arguments\n");
	else if (error == E_FILE_NAME)
		return ("Invalid filename\n");
	else if (error == E_ILLEGAL_CHARS1)
		return ("Illegal characters 1; use only 0123456789.CALplcysp -,\\n\n");
	else if (error == E_ILLEGAL_CHARS2)
		return ("Illegal characters 2: after type of an element\n");
	else if (error == E_ILLEGAL_CHARS3)
		return ("Illegal characters 3: in one of axis or xyz values\n");
	else if (error == E_ILLEGAL_CHARS4)
		return ("Illegal characters 4: in one of alr, lbr, cd, ch, sd values\n");
	else if (error == E_ILLEGAL_CHARS5)
		return ("Illegal characters 5: in one of rgb values\n");
	else if (error == E_MLX_RESIZE)
		return ("MLX resize error\n");
	else if (error == E_ALR_CHARS)
		return ("ALR character error\n");
	else if (error == E_ALR_RANGE)
		return ("ALR range error\n");
	else if (error == E_LBR_CHARS)
		return ("LBR character error\n");
	return (ft_strerror_next(error));
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
		if (write(2, "Error\n", 6) != 6)
			return (5);
		if (write(2, ft_strerror(error), ft_strlen(ft_strerror(error)))
			!= (int)ft_strlen(ft_strerror(error)))
			return (5);
	}
	return (error);
}
