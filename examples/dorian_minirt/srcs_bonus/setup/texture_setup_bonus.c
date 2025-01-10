/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_setup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:49:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/27 08:10:17 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_bonus.h"
#include "errors_bonus.h"
#include "minirt_bonus.h"

static void	get_normals(t_texture **texture)
{
	int		i;
	int		dim;
	int		*dst;
	t_vec4	col;

	dim = (*texture)->picture.width * (*texture)->picture.height;
	(*texture)->picture.norm_vecs = ft_calloc(dim, sizeof(t_vec3));
	if (!(*texture)->picture.norm_vecs)
		ft_error(ENOMEM);
	i = 0;
	while (i < dim)
	{
		dst = (int *)((*texture)->picture.addr + i
				* ((*texture)->picture.bits_per_pixel / 8));
		col = ft_int32tov4(*dst);
		ft_rgbtonorm(&col);
		(*texture)->picture.norm_vecs[i] = (t_vec3){col.x, col.y, col.z};
		(*texture)->picture.norm_vecs[i] = vec3_addf(
				vec3_multf((*texture)->picture.norm_vecs[i], 2),
				- 1);
		i++;
	}
}

static void	get_texture_dim(char **file, int *width, int *height)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(*file, O_RDONLY);
	line = get_next_line(fd, FALSE);
	while (line)
	{
		if (!ft_strncmp(line, "\"", 1))
		{
			tmp = line + 1;
			*width = ft_atoi(tmp);
			ft_skip_num(&tmp, INT, FALSE);
			*height = ft_atoi(tmp);
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd, FALSE);
	}
	get_next_line(fd, TRUE);
	close (fd);
}

static void	get_texels(void *mlx, t_picture *texture)
{
	get_texture_dim(&(texture->file), &(texture->width),
		&(texture->height));
	if (!texture->width || !texture->height)
		ft_error(xpm_err);
	texture->texels = mlx_xpm_file_to_image(mlx, texture->file,
			&(texture->width),
			&(texture->height));
	if (!(texture->texels))
		ft_error(xpm_err);
	texture->addr = mlx_get_data_addr(texture->texels, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

void	set_picture(t_img *img, t_texture **texture, t_vec4 *col, char *line)
{
	char		*tmp;

	tmp = ft_strnstr(line, "-texture", 0xFF);
	if (!tmp)
		return ;
	*texture = ft_calloc(1, sizeof(t_texture));
	if (!*texture)
		ft_error(ENOMEM);
	(*texture)->file = ft_get_word(tmp + 9);
	if (!(*texture)->file)
		ft_error(ENOMEM);
	if (!ft_strncmp((*texture)->file, "checkers", 8))
	{
		set_board(&(*texture)->proc_pat, 10, *col, vec4_multf(*col, 0.5));
		(*texture)->picture.pattern = checkers_pat;
	}
	else if (!ft_strncmp((*texture)->file, "brick", 5))
		(*texture)->picture.pattern = brick_pat;
	else if ((*texture)->file)
	{
		get_texels(img->win.mlx, &(*texture)->picture);
		(*texture)->picture.pattern = colour_pat;
	}
	free((*texture)->file);
}

void	set_normals(t_img *img, t_texture **texture, char *line)
{
	char	*tmp;

	tmp = ft_strnstr(line, "-normal", 0xFF);
	if (!tmp)
		return ;
	*texture = ft_calloc(1, sizeof(t_texture));
	if (!*texture)
		ft_error(ENOMEM);
	(*texture)->file = ft_get_word(tmp + 8);
	if ((*texture)->file)
	{
		get_texels(img->win.mlx, &(*texture)->picture);
		if ((*texture)->picture.texels)
			get_normals(texture);
		(*texture)->picture.pattern = normal_pat;
	}
}
