#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include "../../libft/libft.h"

#define LEGAL_CHARS1 "0123456789.CALplcysp-, \n" //input
#define LEGAL_CHARS2 "0123456789.-, \n" //after assign type
#define LEGAL_CHARS3 "0123456789.-," //3dxyz, xyz, cd, ch, sd
#define LEGAL_CHARS4 "0123456789." //alr, lbr
#define LEGAL_CHARS5 "0123456789," //rgb
#define LEGAL_CHARS6 "0123456789" //fov
#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

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
	E_XYZ_RANGE
}			t_error;

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

typedef struct s_rgb
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
} t_rgb;

typedef struct s_xyz
{
	double x;
	double y;
	double z;
} t_xyz;

typedef struct s_xyz_3d
{
	double x;
	double y;
	double z;
} t_xyz_3d;

typedef struct s_list
{
	char			*s;
	t_type			type;
	float			alr;
	t_rgb			rgb;
	t_xyz			xyz;
	t_xyz_3d		xyz_3d;
	unsigned int	fov;
	float			lbr;
	float			sd;
	float			cd;
	float			ch;
	struct s_list	*next;
}	t_list;

//	  C O N S T A N T S

#ifndef WINSIZE
# define WINSIZE 900
#endif
#define EPSILON 0.00001

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

// Linked list

void ft_lstadd_back(t_list **lst, t_list *new);
t_list *ft_lstlast(t_list *lst);
t_list *ft_lstnew(void *content);

// 	F U N C T I O N S

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
void	init_node(t_list **l);

// 	PROCESS NODES
void	process_nodes(t_list **l);
void	process_node(t_list *current);
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

void	free_array(char **s);



void    check_count_of_types(t_list **l);


// list legality

int	only_legal_chars(char *s, char *legal);
int	list_legality_check(t_list **l, char *legal);



// ERRORS
int	ret_error(t_error error, t_list *l);


//      T E S T S

// void	tests_tuples(void);
// void	tests_colours(void);
// void	tests_canvas(void);
// int		project_one(mlx_image_t *img);
// int		project_one_mlx();
// void	tests_matrix(void);

// //      P R I N T E R S

// void	ft_tuple_print(t_tuple *t);
// void	ft_colour_printer(t_colour *c);
// void	ft_print_line(char c);
// void	print_y(char *s);
// void	print_r(char *s);
// void	print_g(char *s);
// void 	canvas_to_print(t_colour **canvas, int x, int y);

// /*         C R E A T E         */

// t_tuple		*create_tuple(float x, float y, float z, float w);
// t_colour	*create_colour(float r, float g, float b);
// t_tuple		*create_point(float x, float y, float z);
// t_tuple		*create_vector(float x, float y, float z);

// //         F U N C T I O N S (TUPLE?)

// int			diff(t_tuple *t1, t_tuple *t2);
// t_tuple		*add(t_tuple *t1, t_tuple *t2);
// t_tuple		*subtract(t_tuple *t1, t_tuple *t2);
// t_tuple		*negate_tuple(t_tuple *t);
// t_tuple		*multiply_tuple(t_tuple *t, float multiplier);
// t_tuple		*divide_tuple(t_tuple *t, float divisor);
// float		magnitude(t_tuple *t);
// t_tuple		*normalize(t_tuple *t);
// float		dot(t_tuple *a, t_tuple *b);
// t_tuple		*cross(t_tuple *a, t_tuple *b);
// unsigned int float_to_uint(float value);



// //			C O L O U R S

// t_colour   *add_colours(t_colour *a, t_colour *b);
// t_colour   *subtract_colours(t_colour *a, t_colour *b);
// t_colour   *multiply_colour_by(t_colour *a, float scaler);
// t_colour   *hadamard_product(t_colour *a, t_colour *b);
// void		write_pixel(t_colour **canvas, int x, int y, t_colour *colour);

// //			C A N V A S

// t_colour	**create_canvas(int x, int y);
// // size_t 		x_of_canvas(t_colour **canvas);
// // size_t		y_of_canvas(t_colour **canvas);
// int			init_canvas(t_colour **canvas, int x, int y, t_colour *init_value);
// void		canvas_to_ppm(char* filename, t_colour **canvas, int x, int y);

// //			M L X   D R A W I N G

// uint32_t	ft_colour_to_uint32(t_colour *colour);
// void		ft_color_screen(mlx_image_t *img, uint32_t colour);

// 	M A T R I C E S

// float	**matrix_create(int x, int y);
// void	matrix_assign(float **matrix, int x, int y, float f);
// void	matrix_print(float **matrix, int x, int y);
// void	matrix_fill(float **matrix, int x, int y, float f);
// int		matrix_compare(float **matrix1, float **matrix2, int x, int y);
// float	**matrix_multiply(float **matrix1, float **matrix2, int x, int y);
