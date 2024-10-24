/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:43:53 by xriera-c          #+#    #+#             */
/*   Updated: 2024/09/27 13:58:02 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	resize(void *data)
{
	t_rtx		*rtx;
	t_camera	*c;

	rtx = data;
	if (rtx->resize == 1 && mlx_get_time() - rtx->time > 2)
	{
		if (!mlx_resize_image(rtx->img, rtx->width, rtx->height))
			exit(1);
		ft_bzero(rtx->img->pixels, rtx->width * rtx->height * sizeof(uint32_t));
		rtx->resize = 0;
		c = create_camera(rtx->width, rtx->height, rtx->cam->field);
		if (!c)
			exit(1);
		clean_matrix(c->transform, 4);
		c->transform = rtx->cam->transform;
		free(rtx->cam);
		rtx->cam = c;
		render(rtx->cam, rtx->world, rtx->img);
	}
}

void	resize_hook(int32_t w, int32_t h, void *data)
{
	t_rtx	*rtx;

	rtx = data;
	rtx->width = w;
	rtx->height = h;
	rtx->resize = 1;
	rtx->time = mlx_get_time();
}
