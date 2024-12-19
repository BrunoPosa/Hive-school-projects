/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:04:23 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/19 18:27:14 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

// void	init_scene(t_scene *scene)
// {
// 	scene->n_sphere = 0;
// 	scene->n_plane = 0;
// 	scene->n_cylinder = 0;
// 	scene->n_camera = 0;
// 	scene->n_light = 0;
// 	scene->n_ambient = 0;
// }

int	main(int argc, char **argv)
{
	t_rt		all;

	ft_memset(&all, 0, sizeof(t_rt));
	if (import(argc, argv, &all.scene) != E_SUCCESS)
		return (free(all.scene.shapes), E_ERROR);//what if import fails bc of malloc fail!
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
