/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:49:50 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/25 15:30:54 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

void	free_data(t_raydata *data)
{
	if (!data)
		return ;
	free(data);
	data = NULL;
}

int	free_return(void *ptr, t_error error)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (error);
}

void	free_array(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	free_arr_return(char **s, int error)
{
	free_array(s);
	return (error);
}
