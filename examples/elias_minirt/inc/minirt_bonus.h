/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:33:34 by xriera-c          #+#    #+#             */
/*   Updated: 2024/10/17 11:12:03 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../lib/Libft/libft.h"
# include "MLX42/MLX42.h"

# define PI 3.14159265358979323846
# define EPS 0.00001
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

# define ORIGIN 0
# define DIRECTION 1

typedef enum e_shape
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_shape;

typedef enum e_transformation
{
	TRANSLATION,
	SCALING,
	ROTATE,
	SHEARING
}	t_transformation;

typedef struct s_matrix
{
	int					size;
	float				**m;
	t_transformation	type;
}	t_matrix;

typedef struct s_pattern
{
	float		*colora;
	float		*colorb;
	t_matrix	*transf;
}	t_pattern;

typedef struct s_material
{
	float		*color;
	float		*ambient;
	float		diffuse;
	float		specular;
	float		shininess;
	t_pattern	*patt;
	t_bool		pattern;
}	t_material;

typedef struct s_light
{
	float	*color;
	float	brightness;
	float	*coord;
}	t_light;

typedef struct s_cylvals
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t0;
	float	t1;
	float	y0;
	float	y1;
}	t_cylvals;

typedef struct s_object
{
	t_shape		s;
	float		*coord;
	float		diameter;
	t_matrix	*transform;
	float		*normv;
	float		height;
	t_material	*material;
	float		cylindermin;
	float		cylindermax;
	t_bool		closed;
	t_bool		bump;
}	t_object;

typedef struct s_world
{
	int			number_objects;
	t_object	**objects;
	t_light		**lights;
}	t_world;

typedef struct s_comp
{
	t_object	*object;
	float		t;
	float		*point;
	float		*over_point;
	float		*eyev;
	float		*normalv;
	t_bool		inside;
}	t_comp;

typedef struct s_inter
{
	float		t;
	t_object	*object;
}	t_inter;

typedef struct s_inters
{
	int			count;
	t_object	**objects;
	float		*t;
}	t_inters;

typedef struct s_camera
{
	float		hsize;
	float		vsize;
	float		field;
	float		pixel_size;
	float		half_height;
	float		half_width;
	t_matrix	*transform;
}	t_camera;

typedef struct s_lightdot
{
	float		*eff_color;
	float		*lightv;
	float		*ambient;
	float		*tmp;
	float		light_dot_nor;
	float		*diffuse;
	float		*spec;
	t_object	*obj;
	t_light		*l;
	t_comp		*comp;
}	t_lightdot;

typedef struct s_parse
{
	int			amnum;
	int			cnum;
	float		alightr;
	float		*amcolor;
	float		camc[3];
	float		normv[3];
	int			fow;
	t_light		**light;
	int			lightnumb;
	float		lbrightness;
	int			total;
}	t_parse;

typedef struct s_rtx
{
	t_camera	*cam;
	t_world		*world;
	mlx_image_t	*img;
	int32_t		width;
	int32_t		height;
	int			resize;
	mlx_t		*mlx;
	float		time;
}	t_rtx;

/* Parsing */
t_object	**check_file(char *file, t_parse *parse, int flag);
void		free_array(char **args);
void		exit_error(char *msg, char **args, t_parse *parse);
t_bool		validate_values(char *arg);
t_bool		fill_value(char *arg, char **coordinates, float *value);
void		malloc_objects(t_parse *parse);
t_bool		allocate_light(t_parse *parse);
t_bool		validate_light(char **args, t_parse *parse, int index);
t_bool		parse_sphere(char **args, int index, t_object **object,
				t_parse *parse);
t_bool		parse_plane(char **args, int index, t_object **object,
				t_parse *parse);
t_bool		parse_cylinder(char **args, int index, t_object **object,
				t_parse *parse);
t_bool		parse_cone(char **args, int index, t_object **object,
				t_parse *parse);
t_bool		validate_line(char **args, t_parse *parse);
t_bool		fill_rgb(float **color, char *str);
t_bool		check_pattern(t_object **object, int index, char **args, int n);
void		free_objects_exit(t_object **object, char **args,
				int amount, t_parse *parse);

int			colors_to_int(int *colors, int intensity);
float		*combine_colors(float *a, float *b);

/*** MLX ***/
void		start_display(t_camera *c, t_world *w);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		resize_hook(int32_t width, int32_t height, void *param);
void		resize(void *data);

/*** Definitions ***/
float		*tuple(float a, float b, float c, float w);
float		*create_point(float a, float b, float c);
float		*create_vector(float a, float b, float c);
t_matrix	*create_matrix(int n);
t_matrix	*create_populated_matrix(float *a, float *b, float *c, float *d);
float		*color(float a, float b, float c);
t_material	*create_material(t_parse *parse);
t_object	*create_object(t_shape shape, t_parse *parse);
t_matrix	*create_identity(int n);
t_comp		*create_comp(t_inter *i);
t_inters	*create_intersections(int n);
t_comp		*create_comp(t_inter *i);
t_camera	*create_camera(float hsize, float vsize, float field);
t_world		*create_world(int n, t_light **light);
t_light		*create_light(void);

/*** Tuple Operations ***/
int			equal_float(float a, float b);
float		*tuple_add(float *a, float *b);
float		*tuple_subs(float *a, float *b);
float		*negate_vector(float *a);
float		*tuple_add(float *a, float *b);
float		*scalar_multi_tuple(float *a, float n);
float		*scalar_div_tuple(float *a, float n);
float		magnitude(float *a);
float		*normalize(float *a, int delete);
float		dot_product(float *a, float *b);
float		*vector_cross_prod(float *a, float *b);
float		*normal_at(t_object *object, float *world_p);

/*** Matrix operations ***/
int			matrix_are_equal(t_matrix *a, t_matrix *b);
t_matrix	*matrix_multiply(t_matrix *a, t_matrix *b, int delete);
t_matrix	*submatrix(t_matrix *a, int i, int j);
t_matrix	*transpose(t_matrix *a);
float		minor(t_matrix *a, int i, int j);
float		cofactor(t_matrix *a, int i, int j);
float		determinant(t_matrix *a);
t_matrix	*inverse_matrix(t_matrix *a);
float		*four_one_multiply(t_matrix *a, float *b, int delete);

/*** Matrix transformations ***/
t_matrix	*create_translate(float a, float b, float c);
t_matrix	*create_scaling(float a, float b, float c);
t_matrix	*create_x_rotation(float a);
t_matrix	*create_y_rotation(float a);
t_matrix	*create_z_rotation(float a);
t_matrix	*view_transform(float *from, float *to, float *up);
t_matrix	*create_transform(t_matrix *transform, t_object *o);

/*** Rays ***/
float		**create_ray(float *origin, float *direction);
float		*ray_position(float **r, float t);
float		**transform_ray(float **ray, t_matrix *matrix);
float		**ray_for_pixel(t_camera *c, float px, float py);

/*** Cleaning structs ***/
void		clean_material(t_material *mat);
void		clean_object(t_object *obj);
void		clean_matrix(t_matrix *matrix, int n);
void		clean_comp(t_comp *comp);
void		clean_intersections(t_inters *inter);
void		clean_lights(t_light	**lights);
void		clean_ray(float **ray);
void		clean_world(t_world	*w);
void		clean_points(float *a, float *b, float *c, float *d);
void		clean_parse(t_parse *parse);
void		clean_rtx(t_rtx	*rtx, mlx_t	*mlx, mlx_image_t *img);

/*** Intersections ***/
t_inter		*intersection(float t, t_object *object);
t_inter		*hit(t_inters *xs);
t_inters	*sphere_intersect(t_object *sp, float **r);
t_inters	*sort_intersect(t_inters *xs);
t_inters	*intersect_world(t_world *w, float **r);
t_inter		*intersection(float t, t_object *object);
t_inter		*hit(t_inters *xs);
t_inters	*pre_intersect(t_object *object, float **ray);
t_inters	*plane_intersect(t_object *plane, float **ray);
t_inters	*cylinder_intersect(t_object *cylinder, float **ray);
t_comp		*prepare_computations(t_inter *i, float **ray);
t_inters	*cone_intersect(t_object *cone, float **ray);
void		ft_swap(float *a, float *b);
float		*perturb_normal(float *normal, float *point);

/*** Color utils ***/
float		*hadamard(float *a, float *b);
float		*multiply_color(float *a, float b, int delete);
float		*add_colors(float *a, float *b, float *c);
float		*add_two_colors(float *a, float *b);
float		*conv_color_for(float *a);
int			*conv_color_back(float *a);
char		*strjoin_colors(char *s1, char *s2, char *s3);
int			get_digit(char c, int digits_in_base);
char		to_lower(char c);
float		clamp_color(float n);

/*** Color calculations ***/
float		*lighting(t_comp *comp, t_light *l, t_object *obj, int shadow);
float		*shade_hit(t_world	*w, t_comp *comp);
float		*reflect(float *vector, float *normal);
float		*color_at(t_world *w, float **ray);
int			is_shadowed(t_world *w, float *p, t_light *l);
int			render(t_camera *camera, t_world *world, mlx_image_t *img);
t_pattern	*create_pattern(float *a, float *b, t_matrix *transf);
float		*checker_at_obj(t_comp *comp);

#endif
