/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:19:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 23:10:21 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "vector_math_bonus.h"
# include "objects_bonus.h"

# ifndef MAX_LIGHTS
#  define MAX_LIGHTS 6
# endif

typedef union u_object		t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_disk		t_disk;
typedef struct s_triangle	t_triangle;
typedef struct s_cone		t_cone;
typedef struct s_mesh		t_mesh;

typedef struct s_light
{
	t_vec3	pos;
	float	ratio;
	t_vec4	colour;
	int		valid;
}			t_light;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	right;
	t_vec3	up;
	float	aspect_ratio;
	float	fov;
	int		valid;
}			t_camera;

typedef struct s_amb
{
	float	ratio;
	t_vec4	colour;
	int		valid;
}			t_amb;

typedef struct s_scene
{
	t_amb		amb;
	t_light		*lights;
	t_camera	cam;
	int32_t		bounces;
	t_object	*objs;
	int			n_objs;
	int			n_lights;
	float		*distances;
	t_vec3		*directions;
	t_vec4		*specular;
}				t_scene;

void	ft_skip_ws(char **line);
void	ft_skip_num(char **line, int mode, int allow_comma);
int		is_obj(char *line);
t_vec4	get_colour(char **line);
float	get_float(char **line, int mode);
t_vec3	get_vec3(char **line);
void	validate_scene(t_scene *scene);
void	create_sphere(t_sphere *sphere, char *line);
void	create_cylinder(t_cylinder *cylinder, char *line);
void	create_plane(t_plane *plane, char *line);
void	create_disk(t_disk *disk, char *line);
void	create_triangle(t_triangle *triangle, char *line);
void	create_cone(t_cone *cone, char *line);
void	create_mesh(t_mesh *mesh);
void	ascii_parser(t_mesh *mesh, char *line);
t_vec2	get_textures(char *line);
t_vec3	get_vec3_mesh(char *line);
char	*process_vertex(t_mesh *mesh, char *line, int fd);
char	*process_normals(t_mesh *mesh, char *line, int fd);
char	*process_faces(t_mesh *mesh, char *line, int fd);
char	*process_textures(t_mesh *mesh, char *line, int fd);
void	count_file_objects(int fd, t_mesh *mesh);
void	get_faces(char *line, t_vec3_face	*key, t_mesh *mesh);
void	allocate_arrays(t_mesh *mesh);
char	**ft_split3(char const *s, char c, char d);
float	which_pos_min(float a, float b, float c);
void	set_unique(t_scene *scene, char **line);

#endif