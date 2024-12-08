#ifndef FILE_TO_LIST_H
# define FILE_TO_LIST_H

#include "../../MLX42/include/MLX42/MLX42.h"
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

// #ifndef TRUE
# define TRUE 1
// #endif

// #ifndef FALSE
# define FALSE 0
// #endif


//	  C O N S T A N T S

//this is the width of the window in screen pixels
#ifndef WINSIZE
# define WINSIZE 700
#endif

//this is the width of the window in minirt world coordinates
#ifndef WRLD_WINSIZE
# define WRLD_WINSIZE 2.0f
#endif

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#ifndef EPSILON
# define EPSILON 0.00001
#endif

//	  A L I A S E S

#define POINT 1
#define VECTOR 0
#define SUCCESS 0
#define ERROR -1

//	  C O L O U R S

#define YELLOW	"\033[1;33m"
#define GREEN	"\033[1;32m"
#define RED		"\033[0;31m"
#define PINK	"\033[1;95m"
#define ENDCLR	"\033[0m"




//should this be called exit status? return codes?
typedef enum e_error
{
	E_SUCCESS,
	E_ARGS,
	E_FILE_NAME,
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
	E_SPLIT,
	E_MALLOC,
	E_WRONG_TYPE,
	E_EXTRA_CHARS,
	E_XYZ_RANGE,
	E_OBJECT_COUNT
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

typedef struct s_vec
{
	float x;
	float y;
	float z;
} t_vec;

typedef struct s_colour
{
	float r;
	float g;
	float b;
} t_colour;

typedef struct s_xyz
{
	float x;
	float y;
	float z;
} t_xyz;

typedef struct	s_shape
{
	t_type		type;
	t_vec		xyz;
	t_vec		xyz3d;
	t_colour	rgb;
	float		sd;
	float		cd;
	float		ch;
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
	t_colour		rgb;
	t_xyz			xyz;
	t_xyz			xyz_3d;
	unsigned int	fov;
	float			lbr;
	float			sd;
	float			cd;
	float			ch;
	struct s_list	*next;
}	t_list;

//s_elements is for camera
typedef struct s_elements
{
	t_type		type;
	t_vec		pos;
	t_vec		xyz3d;
	float		focal_length;
}	t_elem;

typedef struct	s_data
{
	t_shape		*shape;
	t_vec		hitp;
	t_vec		shadow_ray;
	t_vec		normal;
	t_colour	*shade_color;
	t_colour	*diffuse_color;
	float		hitmin;
} t_data;

// general program info
typedef struct s_scene
{
	float		lbr;
	t_vec		lightpos;
	t_elem		camera;
	t_colour	ambiant;
// cy, pl, and sp objects are all part of a single Shapes[] array, calloc'd to the right size
	t_shape		*shapes;
	t_data		*data;
	int			shape_count;
	int			n_camera;
	int			n_light;
	int			n_ambient;
	int			n_cylinder;
	int			n_sphere;
	int			n_plane;
	float		world_scale;
	float		half_new_winsize;
	int			err_status;

// can we use a link2 to connect objects of the same type?
// then to free we can rip through all the linked list,
// or another way would be to reconnect the nodes to new linked lists
	// t_cy *cylinders;
	// t_pl *planes;
	// t_sp *spheres;
} t_scene;

// data struct for temporary calculation storage for the pixel to be rendered
// typedef struct s_renderdata
// {
// 	// t_vec	color;
// 	int		rgba;
// 	int		x;
// 	int		y;
// 	// t_vec	px_center;
// 	// t_vec	ray_direction;
// 	// t_ray	ray;
// }	t_data;


// Linked list functions
void ft_lstadd_back(t_list **lst, t_list *new);
t_list *ft_lstlast(t_list *lst);
t_list *ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));



//////////////////////////////////////////////////
/*		P A R S I N G    F U N C T I O N S		*/
//////////////////////////////////////////////////

int	parse(int argc, char **argv, t_scene *scene);
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

t_elem	move_element_into_scene(t_list *current);
void	move_shapes_into_scene(t_list **l, t_scene *scene, enum e_type type);
int	allocate_scene_arrays(t_scene *scene);

// 	PROCESS NODES
int		process_nodes(t_list **l);
int		process_node(t_list *current);
int		process_camera(t_list *current);
void	process_cylinder(t_list *current);
void	process_plane(t_list *current);
int		process_light(t_list *current);
void	process_sphere(t_list *current);
int		process_ambiant(t_list *current);
int		process_alr(t_list *current);
int		process_xyz(t_list *current);
int		process_xyz_3d(t_list *current);
int		process_fov(t_list *current);
int		process_lbr(t_list *current);
int		process_sd(t_list *current);
int		process_cd(t_list *current);
int		process_ch(t_list *current);
int		process_rgb(t_list *current);

int count_commas(char *s, int target);
int	count_commas_between(char *s);
int	is_number_valid(char *num);
int    check_count_of_types(t_list **l, t_scene *rt);


// list legality

int	only_legal_chars(char *s, char *legal);
int	list_legality_check(t_list **l, char *legal);

//	SCENE CREATION
int	populate_scene(t_list **l, t_scene *scene);
t_elem	move_element_into_scene(t_list *current);
float	calculate_focal_len(unsigned int fov);
void	precalculate(t_scene *scene);

// ERRORS
int	ret_error(t_error error, t_list *l);

/// free all the memory allocated for the rt struct
void free_rt(t_scene *rt);
void	free_array(char **s);




/////////////////////////////////////////////////////////
/*         R T - P A R T    F U N C T I O N S          */
/////////////////////////////////////////////////////////

void	esc_keyhook(mlx_key_data_t keydata, void *param);
int		render_pixels(t_scene *scene, mlx_image_t *img);
int		trace(t_scene *scene, t_vec ray);
t_vec	calculate_camera_ray(t_scene *scene, t_vec camera, int i, int j);
int		find_closest_shape(t_scene *scene, t_vec ray);
float	shape_intersect(t_vec ray, t_vec ray_origin, t_shape shape);
float	fsphere(t_vec ray, t_vec ray_origin, t_shape sphere);
float	fplane(t_vec ray, t_vec ray_origin, t_shape plane);
t_colour	*calculate_colour(t_scene *scene, t_shape *shape);
int		calculate_diffuse_colour(t_scene *scene, t_shape *shape);
int		shadow_check(t_scene *scene, t_vec shadowray, t_shape *shape);
int		init_trace_data(t_scene *scene);
int		clamp(float n);
int		circle(int x, int y, int center, int radius);

/*         T U P L E S         */

t_vec		create_vec(float x, float y, float z);
t_colour	*create_colour(float r, float g, float b);
// t_vec		create_point(float x, float y, float z);
// t_vec		create_vector(float x, float y, float z);
int			diff(t_vec a, t_vec b);
t_vec		add(t_vec a, t_vec b);
t_vec		subtract(t_vec a, t_vec b);
t_vec		negate_tuple(t_vec t);
t_vec		multiply_tuple(t_vec t, float multiplier);
t_vec		divide_tuple(t_vec t, float divisor);
float		magnitude(t_vec t);
t_vec		normalize(t_vec t);
float		dot(t_vec a, t_vec b);
t_vec		cross(t_vec a, t_vec b);
unsigned int float_to_uint(float value);

//			C O L O U R S

t_colour   *add_colours(t_colour *a, t_colour *b);
t_colour   *subtract_colours(t_colour *a, t_colour *b);
t_colour   *multiply_colour_by(t_colour *a, float scaler);
t_colour   *hadamard_product(t_colour *a, t_colour *b);
uint32_t	ft_colour_to_uint32(t_colour *colour);


//      P R I N T E R S

void	ft_vec_print(t_vec t);
void	ft_colour_printer(t_colour *c);
void	print_y(char *s);
void 	ft_scene_print(t_scene *scene);


// C L E A N U P
void free_data(t_data *data);

#endif