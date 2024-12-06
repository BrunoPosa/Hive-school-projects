/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:42:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:10:53 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_BONUS_H
# define OBJECTS_BONUS_H

# include "scene_bonus.h"
# include "patterns_bonus.h"

typedef union u_object	t_object;
typedef union u_texture	t_texture;

typedef enum e_obj
{
	sphere_obj,
	plane_obj,
	cylinder_obj,
	disk_obj,
	triangle_obj,
	cone_obj,
	mesh_obj
}	t_obj_e;

typedef struct s_meta
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec4			colour;
}					t_meta;

typedef struct s_sphere
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec4			colour;
	t_vec3			pos;
	float			radius;
	float			radius2;
}					t_sphere;

typedef struct s_plane
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec4			colour;
	t_vec3			pos;
	t_vec3			normal;
	int				isvisible;
}					t_plane;

typedef struct s_cylinder
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec4			colour;
	t_vec3			pos;
	t_object		*bottom;
	t_object		*top;
	float			radius;
	float			radius2;
	int				disk_hit;
	t_vec3			normal;
	float			height;
}					t_cylinder;

typedef struct s_disk
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec4			colour;
	t_vec3			pos;
	t_vec3			normal;
	float			radius;
	int				isvisible;
}					t_disk;

typedef struct s_triangle
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec2			uv;
	t_vec4			colour;
	t_vec3			tri_point[3];
	t_vec3			normal;
	t_vec3			edges[2];
}					t_triangle;

typedef struct s_mesh
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec4			colour;
	float			n_triangles;
	float			count_v;
	float			count_vn;
	float			count_vt;
	float			count_f;
	t_vec3			*vertex;
	t_vec3			*normals;
	t_vec2			*textures;
	t_vec3_face		**faces;
	int				obj_id;
	t_object		*triangle_data;
}					t_mesh;

typedef struct s_cone
{
	t_obj_e			type;
	t_texture		*tex_col;
	t_texture		*tex_norm;
	t_vec4			colour;
	t_vec3			pos;
	t_object		*bottom;
	t_vec3			normal;
	float			radius;
	float			radius2;
	float			height;
	float			height2;
	int				disk_hit;
}					t_cone;

typedef union u_object
{
	t_obj_e		type;
	t_meta		meta;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_disk		disk;
	t_triangle	triangle;
	t_mesh		mesh;
	t_cone		cone;
}				t_object;

#endif