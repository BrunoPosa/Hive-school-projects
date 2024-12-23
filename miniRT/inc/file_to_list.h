#ifndef FILE_TO_LIST_H
# define FILE_TO_LIST_H

// not going to work well
#include "../../MLX42/include/MLX42/MLX42.h"

// this is going back too far.
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>


#define LEGAL_CHARS1 "0123456789.CALplcysp-, \n" //input
#define LEGAL_CHARS2 "0123456789.-, \n" //after assign type
#define LEGAL_CHARS3 "0123456789.-," //3dxyz, xyz
#define LEGAL_CHARS4 "0123456789." //alr, lbr
#define LEGAL_CHARS5 "0123456789," //rgb
#define LEGAL_CHARS6 "0123456789" //fov
#define LEGAL_CHARS7 "0123456789.-" //cd, ch, sd


// should we remove?
// #ifndef TRUE
# define TRUE 1
// #endif

// #ifndef FALSE
# define FALSE 0
// #endif


//	  C O N S T A N T S

//this is the width of the window in screen pixels
#ifndef WINSIZE
# define WINSIZE 600
#endif

//this is the width of the window in minirt world coordinates
// #ifndef VIEWPLANE_SIZE
// # define VIEWPLANE_SIZE 2.0f
// #endif

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#ifndef EPSILON
# define EPSILON 0.001f
#endif

//	  A L I A S E S
// not using these any more
// #define POINT 1
// #define VECTOR 0
// #define E_SUCCESS 0
// #define E_ERROR -1

//	  C O L O U R S

#define YELLOW	"\033[1;33m"
#define GREEN	"\033[1;32m"
#define RED		"\033[0;31m"
#define PINK	"\033[1;95m"
#define ENDCLR	"\033[0m"

typedef	struct	s_window
{
	int	w;
	int	h;
}	t_win;

typedef enum	e_coef
{
	a,
	b,
	c
} t_coef;

//should this be called exit status? return codes?
// make an array of strings somehow to print the error
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
	E_PROCESS_NODE,
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
	E_WRONG_TYPE,
	E_EXTRA_CHARS,
	E_XYZ_RANGE,
	E_OBJECT_COUNT,
	E_SPHERE_SD,
	E_CYLINDER_CD,
	E_CYLINDER_CH,
	E_N_OF_TYPES
}			t_error;
// #endif

typedef enum e_type
{
	unassigned,
	camera,
	cylinder,
	plane,
	light,
	sphere,
	ambiant
} t_type;

typedef enum e_hitpart
{
	nothing,
	bottom,
	body,
	top
} t_hpart;

// this could be changed to s_xyz in the code
typedef struct s_vec
{
	float x;
	float y;
	float z;
} t_vec;

// might be calle rgb
typedef struct s_colour
{
	float r;
	float g;
	float b;
} t_colour;

/*
	replaced this with t_vec
	and we can now rename t_vec to t_xyz or triple or whatever we want,
	as long as now t_list and t_scene have the same data type to store xyz coordinates
*/
// typedef struct s_xyz
// {
// 	float x;
// 	float y;
// 	float z;
// } t_xyz;

// do we need to make function to free t_vec? etc? no?
typedef struct	s_shape
{
	t_type		type;
	t_vec		xyz;
	t_vec		axis;
	t_colour	rgb;
	int			part_hit;
	bool		inside;
	float		r;
	float		h;
}	t_shape;

/*
	-s is the string, p is the pointer to the string, which will be moved through the string
*/
typedef struct s_list
{
	char			*s;
	char			*p;
	t_type			type;
	float			alr;
	float			lbr;
	t_colour		rgb;
	t_vec			xyz;
	t_vec			xyz_3d;
	unsigned int	fov;
	float			d;
	float			h;
	struct s_list	*next;
}	t_list;

//s_elements is for camera
typedef struct s_camera
{
	t_vec	eye;//call this xyz
	t_vec	axis;
	t_vec	x_step;
	t_vec	y_step;
	float	foc_len;
}	t_cam;

// temp data for rays, shouldn't need free'd
typedef struct	s_raydata
{
	t_shape		*shape;
	t_vec		hitp;
	t_vec		shadow_ray;
	t_vec		normal;
	t_colour	base_color;
	t_colour	diffuse_part;
	float		hitmin;
} t_raydata;

// general program info
typedef struct s_scene
{
	float		lbr;
	t_vec		lightxyz;
	t_cam		cam;
	t_colour	ambiant;
	t_shape		*shapes;
	int			shape_count;
	int			n_camera;
	int			n_light;
	int			n_ambient;
	int			n_cylinder;
	int			n_sphere;
	int			n_plane;
	t_win		window;
	float		aspect_r;
}	t_scene;

typedef struct s_rt
{
	t_list		*list;
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_rt;

// Linked list functions
void ft_lstadd_back(t_list **lst, t_list *new);
t_list *ft_lstlast(t_list *lst);
t_list *ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));



//////////////////////////////////////////////////
/*		P A R S I N G    F U N C T I O N S		*/
//////////////////////////////////////////////////

int	import(int argc, char **argv, t_scene *scene);
int	file_to_list(char *file_name, t_list **l);
// int		ft_list_push_back(t_list *l, char *content);
void 	ft_list_print(t_list **l);
int		process_list(t_list **l);
void	remove_spaces(t_list **l);
// char*	process(char *s);
// char*	process2(char *s);
int		list_legality_check(t_list **l, char *legal);
int		only_legal_chars(char *s, char* legal);
int	only_legal_chars_n(char *s, char *legal, int n);
int		len_until_space(char *s);

char    *skip_space(char *s);
void	move_pointers_to_args(t_list **l);
int		assign_node_type(t_list **l);
int		does_file_end_with_rt(char *filename);
// void	init_node(t_list **l); //ft_calloc initializes to 0 automatically, we can use that instead

t_cam	move_cam_into_scene(t_list *current);
void	move_shapes_into_scene(t_list **l, t_scene *scene, enum e_type type);
int		allocate_shape_array(t_scene *scene);

// 	PROCESS NODES
int		process_nodes(t_list **l);
int		process_node(t_list *current);
int		process_camera(t_list *current);
int		process_cylinder(t_list *current);
int		process_plane(t_list *current);
int		process_light(t_list *current);
int		process_sphere(t_list *current);
int		process_ambiant(t_list *current);
int		process_alr(t_list *current);
int		process_lbr(t_list *current);
int		process_xyz(t_list *current);
int		process_xyz_3d(t_list *current);
int		process_fov(t_list *current);
int		process_sd(t_list *current);
int		process_cd(t_list *current);
int		process_ch(t_list *current);
int		process_rgb(t_list *current);

int count_commas(char *s, int target);
int	count_commas_between(char *s);
int	is_n_valid(char *num);
int    check_count_of_types(t_list **l, t_scene *rt);


// list legality

int	only_legal_chars(char *s, char *legal);
int	list_legality_check(t_list **l, char *legal);

//	SCENE CREATION
int	populate_scene(t_list **l, t_scene *scene);
t_cam	move_element_into_scene(t_list *current);
float	calculate_focal_len(unsigned int fov);

// E_ERRORS
int	ret_error(t_error error, t_rt *data);

/// free all the memory allocated for the rt struct
void	free_rt(t_scene *rt);
void	free_array(char **s);
void	free_data(t_raydata *data);
int		free_return(void *ptr, t_error error);
int		free_arr_return(char **s, int error);




/////////////////////////////////////////////////////////
/*         R T - P A R T    F U N C T I O N S          */
/////////////////////////////////////////////////////////

void	esc_keyhook(mlx_key_data_t keydata, void *param);
void	resizer(int32_t width, int32_t height, void* param);
void	render_image(t_scene *scene, mlx_image_t *img);
int		trace(t_scene *scene, t_vec ray);
t_vec 	viewplane_offsets(t_scene *scene, t_vec eye);
bool	closest_shape_hit(t_scene *scene, t_vec ray, t_raydata *rayd);
float	intersect_all(t_vec ray, t_vec origin, t_shape *shape);
float	fsphere(t_vec ray, t_vec origin, t_shape *sphere);
float	fplane(t_vec ray, t_vec origin, t_shape *plane);
float	fcylinder(t_vec ray, t_vec origin, t_shape *cyl);
float	intersect_cyl_caps(t_vec ray, t_vec origin, t_shape *cyl);
bool	is_point_inside_cyl(t_vec origin, t_shape *cyl);
float	cyl_height_check(t_vec ray, t_vec origin, float t, t_shape *cyl);
float	cyl_radius_check(t_vec ray, t_vec origin, float t, t_shape *cap);
t_vec	cyl_normal(t_raydata *rayd, t_shape *cyl);
t_vec	surface_normal(t_scene *scene, t_shape *shape, t_raydata *rayd);
t_colour	calc_diffuse_part(t_scene *scene, t_shape *shape, t_raydata *rayd);
bool	is_backlit(t_scene *scene, t_shape *plane, t_raydata *rayd);
bool	in_shadow(t_scene *scene, t_raydata *rayd);

/*         T U P L E S         */

t_vec		create_vec(float x, float y, float z);
t_colour	create_colour(float r, float g, float b);
// t_vec		create_point(float x, float y, float z);
// t_vec		create_vector(float x, float y, float z);
int			diff(t_vec a, t_vec b);
t_vec		add(t_vec a, t_vec b);
t_vec		subtract(t_vec a, t_vec b);
t_vec		negate(t_vec t);
t_vec		scale(t_vec t, float scaler);
// t_vec		divide_tuple(t_vec t, float divisor);
float		magnitude(t_vec t);
t_vec		normalize(t_vec t);
float		dot(t_vec a, t_vec b);
t_vec		cross(t_vec a, t_vec b);
// unsigned int float_to_uint(float value);

//			C O L O U R S

t_colour	add_colours(t_colour a, t_colour b);
t_colour	subtract_colours(t_colour a, t_colour b);
t_colour	scale_colour(t_colour a, float scaler);
t_colour	hadamard_product(t_colour a, t_colour b);
uint32_t	to_uint32(t_colour colour);
t_colour	scale_colour_channels(t_colour a);
float		clamp(float n);
t_colour	black(void);


//      P R I N T E R S

void	ft_vec_print(t_vec t);
void	ft_colour_printer(t_colour c);
void	print_y(char *s);
void 	ft_scene_print(t_scene *scene);

#endif
