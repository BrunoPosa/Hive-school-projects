/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 02:10:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# ifdef __APPLE__
#  include "macos_keys.h"
# else
#  include "linux_keys.h"
# endif
# include "scene.h"
# include "libft.h"
# include "errors.h"

# define WIDTH 500
# define HEIGHT 500

# define BOUNCES 1
# define EXT_LEN 3
# define EXTENSION ".rt"
# define RATIO 0
# define REAL 1
# define BALANCE 2
# define INT 3
# define ANGLE 4
# define EPSILON 10e-6

# define TRUE 1
# define FALSE 0

# define ORTHO 0
# define AXIS 1

typedef struct s_scene	t_scene;

typedef struct s_window
{
	void	*mlx;
	void	*win;
}			t_window;

typedef struct s_img
{
	t_window	win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	float		aspect_ratio;
	t_scene		*scene;
	int			error;
}				t_img;

// MINIRT
void	set_image(t_img *img);
void	set_scene(t_img *img, t_scene *scene, char *av);
void	render(t_img *img);
void	free_img(t_img *img);

// INPUT HANDLERS
int		user_input(t_img *img);
int		ft_close(t_img *img);
int		key_handler(int key, t_img *img);

// COLOUR FUNCTIONS
int32_t	create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif
