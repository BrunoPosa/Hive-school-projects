/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:19:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:08:17 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_math.h"
# include "objects.h"

typedef union u_object		t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_disk		t_disk;
typedef struct s_triangle	t_triangle;
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
void	check_line(char **line);
void	create_sphere(t_sphere *sphere, char *line);
void	create_cylinder(t_cylinder *cylinder, char *line);
void	create_plane(t_plane *plane, char *line);
void	create_disk(t_disk *disk, char *line);
float	which_pos_min(float a, float b, float c);
void	set_unique(t_scene *scene, char **line);
void	check_visibility(t_scene *scene, int id);

#endif