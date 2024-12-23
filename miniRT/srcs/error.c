/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:42:47 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 17:21:14 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"
#include "../../libft/libft.h"


static char	*ft_strerror(t_error error)
{
	if (error == E_ARGS)
		return ("Invalid arguments");
	else if (error == E_FILE_NAME)
		return ("file name");
	else if (error == E_ILLEGAL_CHARS1)
		return ("chars 1");
	else if (error == E_ILLEGAL_CHARS2)
		return ("chars 2");
	else if (error == E_ILLEGAL_CHARS3)
		return ("chars 3");
	else if (error == E_ILLEGAL_CHARS4)
		return ("chars 4");
	else if (error == E_ILLEGAL_CHARS5)
		return ("chars 5");
	else if (error == E_ALR_CHARS)
		return ("alr chars");
	else if (error == E_ALR_RANGE)
		return ("alr range");
	else if (error == E_LBR_CHARS)
		return ("lbr chars");
	else if (error == E_LBR_RANGE)
		return ("lbr range");
	else if (error)
		return ("We need to build out the error messages");
	return ("We need to build out the error messages");
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
	// printf("%s==== Hold your horses! VALIDATION FAILED ====%s\nerrno: %u\n", YELLOW, ENDCLR, error);
	}
	return (error);
}
