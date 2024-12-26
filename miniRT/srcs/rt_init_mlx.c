/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:51:46 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/26 02:04:46 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	init_mlx(t_scene *rt)
{
	rt->mlx = mlx_init(rt->width, rt->height, "miniRT", true);
	if (!rt->mlx)
	{
		// 'mlx_init failed' error message
        // free and exit
	}
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img)
	{
		// mlx_new_image fail message;
    	// free and exit
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
	{
        // mlx_image_to_window failed message
        // free and exit
	}
	mlx_loop_hook(rt->mlx, &close_hook, rt->mlx);
}
