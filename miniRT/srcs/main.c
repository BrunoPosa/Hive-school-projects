/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:04:23 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/15 16:03:16 by bposa            ###   ########.fr       */
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
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;

	mlx = NULL;
	img = NULL;
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (ret_error(E_MALLOC, NULL));
	// init_scene(scene);
	if (import(argc, argv, scene) != E_SUCCESS)
		return (free(scene), E_ERROR);
	mlx = mlx_init(WINSIZE, WINSIZE, "minirt", false);
	if (!(mlx))
		return (free(scene), E_ERROR);
	img = mlx_new_image(mlx, WINSIZE, WINSIZE);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (free(scene), mlx_terminate(mlx), E_ERROR);
	render_image(scene, img);
	mlx_key_hook(mlx, &esc_keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (free(scene), E_SUCCESS);
}
