/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:04:23 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 04:00:20 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

int	main(int argc, char **argv)
{
// usually these are called data?
	t_rt		all;
	// we need to be putting the list into the r_rt
	// so that we can pass it to the error exit function
int status = 0;

	ft_memset(&all, 0, sizeof(t_rt));

// this should pass in 'all' or 'data', and then only access what it needs from within the functions
	status = import(argc, argv, &all.scene);
	
	printf("status: %d\n", status);
	
	if (status)
		ret_error(status, &all);
		
// this is freeing only the shapes, what about the rest of r_rt?
		// return( status, t_rt)
		// return (free(all.scene.shapes), E_ERROR);//what if import fails bc of malloc fail!

// put in the fucntion that checks the return value of the inmort and frees if there is problem
// ret error?

	all.mlx = mlx_init(WINSIZE, WINSIZE, "minirt", true);
	
	if (!(all.mlx))
		return (free(all.scene.shapes), E_ERROR);//?!
	all.img = mlx_new_image(all.mlx, WINSIZE, WINSIZE);
	if (!all.img || mlx_image_to_window(all.mlx, all.img, 0, 0) < 0)
		return (free(all.scene.shapes), mlx_terminate(all.mlx), E_ERROR);//!
	render_image(&all.scene, all.img);
	mlx_key_hook(all.mlx, &esc_keyhook, &all);
	mlx_resize_hook(all.mlx, &resizer, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (free(all.scene.shapes), E_SUCCESS);//!
	// return(ret_error(status, &all));
}
