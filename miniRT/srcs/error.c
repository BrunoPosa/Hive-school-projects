/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:42:47 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/22 17:11:03 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

// int	main(int argc, char **argv)
// {
// 	t_data		data;
// 	t_error		exit_code;

// 	if (argc < 5 || argc > 6)
// 		return (ret_error(E_ARGS, NULL));
// 	if (check_input(argv))
// 		return (ret_error(E_ARGS, NULL));
// 	if (check_args(&data, argv))
// 		return (ret_error(E_ARGS, &data));
// 	if (to_malloc(&data))
// 		return (ret_error(E_MALLOC, &data));
// 	if (init_mutexes(&data))
// 		return (ret_error(E_MUTEX, &data));
// 	if (init_philos(&data))
// 		return (ret_error(E_THREAD, &data));
// 	exit_code = start_threads(&data);
// 	if (exit_code != NO_E_ERROR)
// 		return (exit_code);
// 	return (ret_error(NO_E_ERROR, &data));
// }


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
	else if (error == E_SUCCESS)
		return ("E_SUCCESS");
	return (NULL);
}

// static void	destroy_mutex(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->ph_count)
// 	{
// 		if (data->phs[i].mutex_last_meal.init)
// 			pthread_mutex_destroy(&data->phs[i].mutex_last_meal.mutex);
// 		if (data->phs[i].mutex_meals_eaten.init)
// 			pthread_mutex_destroy(&data->phs[i].mutex_meals_eaten.mutex);
// 		if (data->phs[i].mutex_done.init)
// 			pthread_mutex_destroy(&data->phs[i].mutex_done.mutex);
// 		if (data->forks[i].init)
// 			pthread_mutex_destroy(&data->forks[i].mutex);
// 	}
// 	if (data->mutex_msg.init)
// 		pthread_mutex_destroy(&data->mutex_msg.mutex);
// 	if (data->mutex_died.init)
// 		pthread_mutex_destroy(&data->mutex_died.mutex);
// }


int	ret_error(t_error error, t_list *l)
// int	ret_error(t_error error, t_list *l, t_rt *rt)
{
	// (void)rt;	
	(void)l;
	(void)ft_strerror(error);
	// if (l)
	// {
	// 	// if (l->s)
	// 	// 	free(l->s);
	// 	// if (l->rgb.b)
	// 	// 	free(l->rgb.b);
	// 	// if (l)
	// 		free(l);
	// }
	if (error)
	{
		printf("%s==== Hold your horses! VALIDATION FAILED ====%s\nerrno: %u\n", YELLOW, ENDCLR, error);
		// write(2, ft_strerror(error), ft_strlen(ft_strerror(error)));
		// write(2, "\n", 1);
		return ((int)error);
	}
	return (0);
}
