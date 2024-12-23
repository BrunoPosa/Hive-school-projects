/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:49:50 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/11 18:21:08 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free(data);
	data = NULL;
}

// if we keep the list as one list, we can free like that?

// or we coudl section the list into different bits?

// free_list(t_scene *rt)
// {
// if there is a next, go there
// free that, go back?
// recursive?
// }
//
//
/// free all the memory allocated for the rt struct
// void free_rt(t_scene *rt)
// {
// 	free(rt->mlx);
// 	free(rt->img);
// 	free(rt->light);
// 	free(rt->camera);
// 	free(((void*)rt->ambiant));
// 	free_list(rt->cylinder);
// 	free_list(rt->plane);
// 	free_list(rt->sphere);
// 	(rt);
// }

int	free_return(void *ptr, t_error error)
{
	if (ptr)
		free(ptr);
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
