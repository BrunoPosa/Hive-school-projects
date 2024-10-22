#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 0.00001

//	  A L I A S E S
#define POINT 1
#define VECTOR 0
#define SUCESS 0
#define ERROR -1

//	  C O L O U R S
#define YELLOW	"\033[1;33m"
#define GREEN	"\033[1;32m"
#define RED		"\033[0;31m"
#define PINK	"\033[1;95m"
#define ENDCLR	"\033[0m"

typedef struct s_tuple
{
	float x;
	float y;
	float z;
	float w;
} t_tuple;

typedef struct s_colour
{
	float r;
	float g;
	float b;
} t_colour;

//      T E S T S
void	tests(void);
void	tests_colours(void);

//      P R I N T E R S
void	ft_tuple_print(t_tuple *t);
void	ft_colour_printer(t_colour *c);
void	ft_print_line(char c);
void	print_y(char *s);
void	print_r(char *s);
void	print_g(char *s);

//         C R E A T E
//create_tuple() takes in w which can be POINT or VECTOR macro (or a value we don't know yet)
t_tuple		*create_tuple(float x, float y, float z, float w);
t_colour	*create_colour(float r, float g, float b);
// where is create_vector or create_point?!

//         F U N C T I O N S
int			diff(t_tuple *t1, t_tuple *t2);
t_tuple		*add(t_tuple *t1, t_tuple *t2);
t_tuple		*subtract(t_tuple *t1, t_tuple *t2);
t_tuple		*negate_tuple(t_tuple *t);
t_tuple		*multiply_tuple(t_tuple *t, float multiplier);
t_tuple		*divide_tuple(t_tuple *t, float divisor);
float		magnitude(t_tuple *t);
t_tuple		*normalize(t_tuple *t);
float		dot(t_tuple *a, t_tuple *b);
t_tuple		*cross(t_tuple *a, t_tuple *b);


//			C O L O U R S
t_colour   *add_colours(t_colour *a, t_colour *b);
t_colour   *subtract_colours(t_colour *a, t_colour *b);
t_colour   *multiply_colour_by(t_colour *a, float scaler);
t_colour   *multiply_colours(t_colour *a, t_colour *b);
