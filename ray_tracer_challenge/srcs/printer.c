#include "../inc/ray_tracer.h"

void	ft_tuple_print(t_tuple *t)
{
	if (!t)
	{
		printf("%sError: tuple is NULL%s\n", RED, ENDCLR);
		return ;
	}
	printf("x: %.3f | y: %.3f | z: %.3f | w: %.1f %s\n",
			t->x, t->y, t->z, t->w,
			t->w == 0 ? "(VECTOR)" : t->w == 1 ? "(POINT)" : "(neither)");
}

void	ft_print_line(char c)
{
	int i;

	i = 0;
	while (i < 62)
	{
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
}

 void	print_y(char *s)
 {
	printf("%s%s%s", YELLOW, s, ENDCLR);
 }

  void	print_r(char *s)
 {
	printf("%s%s%s", RED, s, ENDCLR);
 }

 void	print_g(char *s)
 {
	printf("%s%s%s", GREEN, s, ENDCLR);
 }


void	ft_colour_printer(t_colour *c)
{
		if (!c)
	{
		printf("%sError: colour tuple is NULL%s\n", RED, ENDCLR);
		return ;
	}
	printf("r: %.3f | g: %.3f | b: %.3f\n", c->r, c->g, c->b);
}