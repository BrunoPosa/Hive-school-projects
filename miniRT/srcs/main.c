/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:04:23 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/25 16:48:02 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	main(int argc, char **argv)
{
	t_rt	data;

	ft_memset(&data, 0, sizeof(t_rt));
	data.errcode = import(argc, argv, &data);
	if (data.errcode)
		return (clean_return(data.errcode, &data));
	data.mlx = mlx_init(WINSIZE, WINSIZE, "minirt", true);
	if (!data.mlx)
		return (clean_return(E_MLX_INIT, &data));
	data.img = mlx_new_image(data.mlx, WINSIZE, WINSIZE);
	if (!data.img || mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
		return (clean_return(E_MLX_IMG, &data));
	render_image(&data.scene, data.img);
	mlx_key_hook(data.mlx, &esc_keyhook, &data);
	mlx_resize_hook(data.mlx, &resizer, &data);
	mlx_loop(data.mlx);
	return (clean_return(data.errcode, &data));
}
