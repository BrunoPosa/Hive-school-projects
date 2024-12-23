/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:04:23 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 13:58:50 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	main(int argc, char **argv)
{
	int		status;
	t_rt	data;

	status = 0;
	ft_memset(&data, 0, sizeof(t_rt));
	status = import(argc, argv, &data);
	printf("status: %d\n", status);
	if (status)
		return(ret_error(status, &data));
	data.mlx = mlx_init(WINSIZE, WINSIZE, "minirt", true);
	if (!(data.mlx))
		return (free(data.scene.shapes), E_ERROR);//?!
	data.img = mlx_new_image(data.mlx, WINSIZE, WINSIZE);
	if (!data.img || mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
		return (free(data.scene.shapes), mlx_terminate(data.mlx), E_ERROR);//!
	render_image(&data.scene, data.img);
	mlx_key_hook(data.mlx, &esc_keyhook, &data);
	mlx_resize_hook(data.mlx, &resizer, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return(ret_error(status, &data));
}
