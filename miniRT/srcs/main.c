/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:04:23 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 13:33:18 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	main(int argc, char **argv)
{
	t_rt	data;
	// we need to be putting the list into the r_rt
	// so that we can pass it to the error exit function
	int status = 0;

	ft_memset(&data, 0, sizeof(t_rt));
	status = import(argc, argv, &data);
	
	printf("status: %d\n", status);
	
	if (status)
		return(ret_error(status, &data));
// this is freeing only the shapes, what about the rest of r_rt?
		// return( status, t_rt)
		// return (free(data.scene.shapes), E_ERROR);//what if import fails bc of malloc fail!

// put in the fucntion that checks the return value of the inmort and frees if there is problem
// ret error?

	// data.mlx = mlx_init(WINSIZE, WINSIZE, "minirt", true);
	// if (!(data.mlx))
	// 	return (free(data.scene.shapes), E_ERROR);//?!
	// data.img = mlx_new_image(data.mlx, WINSIZE, WINSIZE);
	// if (!data.img || mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
	// 	return (free(data.scene.shapes), mlx_terminate(data.mlx), E_ERROR);//!
	// render_image(&data.scene, data.img);
	// mlx_key_hook(data.mlx, &esc_keyhook, &data);
	// mlx_resize_hook(data.mlx, &resizer, &data);
	// mlx_loop(data.mlx);
	// mlx_terminate(data.mlx);
	return (free(data.scene.shapes), E_SUCCESS);//!
	// return(ret_error(status, &all));
}
