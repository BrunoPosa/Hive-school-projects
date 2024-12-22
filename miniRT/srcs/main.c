/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:04:23 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/22 17:13:11 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

/*
These are the same:

	if (import(argc, argv, &all.scene) != E_SUCCESS)
	if (import(argc, argv, &all.scene) != 0)

	while (*s)
	
	if (import(argc, argv, &all.scene))
		return (abna)

*/

int	main(int argc, char **argv)
{
	t_rt		all;
int status = 0;

	ft_memset(&all, 0, sizeof(t_rt));
	status = import(argc, argv, &all.scene);
	printf("status: %d\n", status);
	if (status)
// this is freeing only the shapes, what about the rest of r_rt?
		// return( status, t_rt)
		return (free(all.scene.shapes), E_ERROR);//what if import fails bc of malloc fail!

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
}
