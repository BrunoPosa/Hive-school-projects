/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:42:47 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 13:33:06 by jwadding         ###   ########.fr       */
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
void	free_rt2(t_rt *data)
{
	if (data->list)
		ft_lstclear(&data->list, free);
		// ft_lstclear(&l, free) // from the other part of the code
	// if (data.scene)
	// 	free(data.scene);
	// if (data.mlx)
	// 	free(data.mlx);
	//if (data.img)
	//	free(data.img);
}
/*
This function will free anything that exists in the struct
and then print the error message on stderr.
it will only be called if there is an error in the status.
*/
int	ret_error(t_error error, t_rt *data)
{
	free_rt2(data);
	
	if (error)
	{
		// printf("%s==== Hold your horses! VALIDATION FAILED ====%s\nerrno: %u\n", YELLOW, ENDCLR, error);
		write(2, ft_strerror(error), ft_strlen(ft_strerror(error)));
		write(2, "\n", 1);
		return ((int)error);
	}
	return (0);
}
