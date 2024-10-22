#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 0.00001

//	  A L I A S E S
#define POINT 1
#define VECTOR 0

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
	// t_type w;
	float w;
} t_tuple;

//      T E S T S
void	tests(void);

//      P R I N T E R S
void	ft_tuple_print(t_tuple *t);
void	ft_print_line(char c);

//         C R E A T E

t_tuple *create_tuple(float x, float y, float z, float w);

//         F U N C T I O N S
int		diff(t_tuple *t1, t_tuple *t2);
t_tuple	*add(t_tuple *t1, t_tuple *t2);
t_tuple	*subtract(t_tuple *t1, t_tuple *t2);
t_tuple	*negate_tuple(t_tuple *t);
t_tuple	*multiply_tuple(t_tuple *t, float multiplier);
t_tuple	*divide_tuple(t_tuple *t, float divisor);
float	magnitude(t_tuple *t);
t_tuple	*normalize(t_tuple *t);
float	dot(t_tuple *a, t_tuple *b);
t_tuple	*cross(t_tuple *a, t_tuple *b);
