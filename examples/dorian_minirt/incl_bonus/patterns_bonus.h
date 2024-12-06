/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:03:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 17:45:37 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_BONUS_H
# define PATTERNS_BONUS_H

# include "objects_bonus.h"
# include "scene_bonus.h"
# include "vector_math_bonus.h"
# include "minirt_bonus.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef M_1_DIV_PI
#  define M_1_DIV_PI 0.31830988618379067
# endif
# ifndef M_1_DIV_2PI
#  define M_1_DIV_2PI 0.15915494309189535
# endif
# ifndef U
#  define U 0
# endif
# ifndef V
#  define V 1
# endif

typedef struct s_img	t_img;
typedef union u_object	t_object;
typedef union u_texture	t_texture;

typedef t_vec2			(*t_map_func)(t_vec3 *, t_object *);
typedef t_vec4			(*t_col_func)(t_texture *, t_vec2);

typedef enum e_pattern
{
	no_pat,
	checkers_pat,
	brick_pat,
	colour_pat,
	normal_pat
}	t_pattern;

typedef struct s_proc_pat
{
	char		*file;
	t_pattern	pattern;
	int			width;
	int			height;
	t_vec4		light;
	t_vec4		dark;
}				t_proc_pat;

typedef struct s_picture
{
	char		*file;
	t_pattern	pattern;
	int			width;
	int			height;
	void		*texels;
	t_vec3		*norm_vecs;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}			t_picture;

typedef union u_texture
{
	char		*file;
	t_proc_pat	proc_pat;
	t_picture	picture;
	t_picture	normal;
}				t_texture;

t_vec2		spherical_map(t_vec3 *point, t_object *obj);
t_vec2		cylinder_map(t_vec3 *point, t_object *obj);
t_vec2		plane_map(t_vec3 *point, t_object *obj);
t_vec2		disk_map(t_vec3 *point, t_object *obj);
t_vec2		triangle_map(t_vec3 *point, t_object *obj);
t_vec2		cone_map(t_vec3 *point, t_object *obj);

t_vec4		get_checkers(t_texture *checkers, t_vec2 uv);
void		set_board(t_proc_pat *board, int dim, t_vec4 light, t_vec4 dark);
t_vec4		get_brick(t_texture *texture, t_vec2 uv);

void		set_picture(t_img *img, t_texture **texture, t_vec4 *col,
				char *line);
void		set_normals(t_img *img, t_texture **texture, char *line);
t_vec3		get_texture_norm(t_texture *texture, t_vec2 uv);
void		get_texture_info(t_object *object, t_vec3 *point,
				t_vec4 *colour, t_vec3 *normal);

#endif