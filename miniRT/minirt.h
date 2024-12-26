/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:18:10 by bposa             #+#    #+#             */
/*   Updated: 2024/12/26 04:10:56 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

/*
	1 - input
	2 - after assign type
	3 - 3dxyz, xyz
	4 - alr, lbr
	5 - rgb
	6 - fov
	7 - cd, ch, sd
*/
# define LEGAL_CHARS1 "0123456789.CALplcysp-, \n"
# define LEGAL_CHARS2 "0123456789.-, \n"
# define LEGAL_CHARS3 "0123456789.-,"
# define LEGAL_CHARS4 "0123456789."
# define LEGAL_CHARS5 "0123456789,"
# define LEGAL_CHARS6 "0123456789"
# define LEGAL_CHARS7 "0123456789.-"

//	  C O N S T A N T S

# ifndef WINSIZE
#  define WINSIZE 600
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef EPSILON
#  define EPSILON 0.001f
# endif

# ifndef SHAPE_LIMIT
#  define SHAPE_LIMIT 150
# endif

typedef enum e_error
{
	E_SUCCESS,
	E_ERROR,
	E_ARGS,
	E_OPEN_CLOSE_ERROR,
	E_FILE_NAME,
	E_ILLEGAL_CHARS_GENERAL,
	E_ILLEGAL_CHARS1,
	E_ILLEGAL_CHARS2,
	E_ILLEGAL_CHARS3,
	E_ILLEGAL_CHARS4,
	E_ILLEGAL_CHARS5,
	E_ALR_CHARS,
	E_ALR_RANGE,
	E_LBR_CHARS,
	E_LBR_RANGE,
	E_XYZ_CHARS,
	E_XYZ_COMMA,
	E_FLOAT_CHARS,
	E_UINT_CHARS,
	E_FOV_RANGE,
	E_RGB_CHARS,
	E_RGB_COMMA,
	E_RGB_RANGE,
	E_XYZ_3D_CHARS,
	E_XYZ_3D_COMMA,
	E_XYZ_3D_NORMALIZE,
	E_SPLIT,
	E_MALLOC,
	E_GNL,
	E_WRONG_TYPE,
	E_EXTRA_CHARS,
	E_XYZ_RANGE,
	E_OBJECT_COUNT,
	E_SPHERE_SD,
	E_CYLINDER_CD,
	E_CYLINDER_CH,
	E_MLX_INIT,
	E_MLX_IMG,
	E_MLX_RESIZE,
	E_SHAPE_LIMIT
}	t_error;

typedef enum e_coef
{
	a,
	b,
	c
}	t_coef;

typedef enum e_type
{
	unassigned,
	camera,
	cylinder,
	plane,
	light,
	sphere,
	ambiant
}	t_type;

typedef enum e_hitpart
{
	nothing,
	bottom,
	body,
	top
}	t_hpart;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_colour
{
	float	r;
	float	g;
	float	b;
}	t_rgb;

typedef struct s_shape
{
	t_type	type;
	t_vec	xyz;
	t_vec	axis;
	t_rgb	rgb;
	int		part_hit;
	bool	inside;
	float	r;
	float	h;
}	t_shape;

typedef struct s_list
{
	char			*s;
	char			*p;
	int				type;
	float			alr;
	float			lbr;
	t_rgb			rgb;
	t_vec			xyz;
	t_vec			xyz_3d;
	unsigned int	fov;
	float			d;
	float			h;
	struct s_list	*next;
}	t_list;

typedef struct s_camera
{
	t_vec	eye;
	t_vec	axis;
	t_vec	x_step;
	t_vec	y_step;
	t_vec	up;
	float	foc_len;
}	t_cam;

typedef struct s_raydata
{
	t_shape	*shape;
	t_vec	hitp;
	t_vec	shadow_ray;
	t_vec	normal;
	t_rgb	base_color;
	t_rgb	diffuse_part;
	float	hitmin;
}	t_raydata;

typedef struct s_window
{
	int	w;
	int	h;
}	t_win;

typedef struct s_scene
{
	float	lbr;
	t_vec	lightxyz;
	t_cam	cam;
	t_rgb	ambiant;
	t_shape	*shapes;
	int		shape_count;
	int		n_camera;
	int		n_light;
	int		n_ambient;
	int		n_cylinder;
	int		n_sphere;
	int		n_plane;
	t_win	window;
	float	aspect_r;
}	t_scene;

typedef struct s_rt
{
	t_list		*l;
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_error		errcode;
}	t_rt;

//////////////////////////////////////////////////
/*		P A R S I N G    F U N C T I O N S		*/
//////////////////////////////////////////////////

int			import(int argc, char **argv, t_rt *data);
int			file_to_list(char *filename, t_list **l, int *fd_close_check);
void		ft_list_print(t_list **l);
int			process_list(t_list **l);
void		remove_spaces(t_list **l);
int			list_legality_check(t_list **l, char *legal);
int			only_legal_chars(char *s, char *legal);
int			len_until_space(char *s);
char		*skip_space(char *s);
int			assign_node_type(t_list **l);
int			does_file_end_with_rt(char *filename);
t_cam		move_cam_into_scene(t_list *current);
void		move_shapes_into_scene(t_list **l, t_scene *scene, int type);
int			count_commas(char *s, int target);
int			count_commas_between(char *s);
int			is_n_valid(char *num);
int			check_count_of_types(t_list **l, t_scene *scene);
int			process_nodes(t_list **l);
int			process_camera(t_list *current);
int			process_cylinder(t_list *current);
int			process_plane(t_list *current);
int			process_light(t_list *current);
int			process_sphere(t_list *current);
int			process_ambiant(t_list *current);
int			process_alr(t_list *current);
int			process_lbr(t_list *current);
int			process_xyz(t_list *current);
int			process_xyz_3d(t_list *current);
int			process_fov(t_list *current);
int			process_sd(t_list *current);
int			process_cd(t_list *current);
int			process_ch(t_list *current);
int			process_rgb(t_list *current);
int			populate_scene(t_list **l, t_scene *scene);
t_cam		move_element_into_scene(t_list *current);
float		calculate_focal_len(unsigned int fov);

/*			Cleanup functions			*/

int			clean_return(t_error error, t_rt *data);
void		free_array(char **s);
int			free_return(void *ptr, t_error error);
int			free_arr_return(char **s, int error);

/*			Linked list functions		*/

void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));

/////////////////////////////////////////////////////////
/*         R T - P A R T    F U N C T I O N S          */
/////////////////////////////////////////////////////////

void		esc_keyhook(mlx_key_data_t keydata, void *param);
void		resizer(int32_t width, int32_t height, void *param);
void		render_image(t_scene *scene, mlx_image_t *img);
int			trace(t_scene *scene, t_vec ray);
t_vec		viewplane_offsets(t_scene *scene, t_vec eye);
bool		closest_shape_hit(t_scene *scene, t_vec ray, t_raydata *rayd);
float		intersectall(t_vec ray, t_vec origin, t_shape *shape);
float		fsphere(t_vec ray, t_vec origin, t_shape *sphere);
float		fplane(t_vec ray, t_vec origin, t_shape *plane);
float		fcylinder(t_vec ray, t_vec origin, t_shape *cyl);
float		intersect_cyl_caps(t_vec ray, t_vec origin, t_shape *cyl);
float		cyl_height_check(t_vec ray, t_vec origin, float t, t_shape *cyl);
float		cyl_radius_check(t_vec ray, t_vec origin, float t, t_shape *cap);
t_vec		surface_normal(t_scene *scene, t_shape *shape, t_raydata *rayd);
t_rgb		calc_diffuse_part(t_scene *scene, t_shape *shape, t_raydata *rayd);
bool		in_shadow(t_scene *scene, t_raydata *rayd);

/*         T U P L E S         */

t_vec		create_vec(float x, float y, float z);
t_vec		add(t_vec a, t_vec b);
t_vec		subtract(t_vec a, t_vec b);
t_vec		negate(t_vec t);
t_vec		scale(t_vec t, float scaler);
float		magnitude(t_vec t);
t_vec		normalize(t_vec t);
float		dot(t_vec a, t_vec b);
t_vec		cross(t_vec a, t_vec b);

/*			C O L O U R S		*/

t_rgb		create_colour(float r, float g, float b);
t_rgb		add_colours(t_rgb a, t_rgb b);
t_rgb		scale_colour(t_rgb a, float scaler);
t_rgb		hadamard_product(t_rgb a, t_rgb b);
uint32_t	to_uint32(t_rgb colour);
float		clamp(float n);
t_rgb		black(void);

#endif
