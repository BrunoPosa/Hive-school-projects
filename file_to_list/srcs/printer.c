#include "../inc/file_to_list.h"

void	ft_list_print(t_list **l)
{
	int i;
	t_list *tmp;

	i = 0;
	tmp = *l;
	while (tmp)
	{
		printf("\n--- Node %d start ---\n\n", i);
		printf("s = %s", tmp->s);
		printf("      type = %d\n", tmp->type);
		// printf("       alr = %f\n", tmp->alr);
		// printf("     rgb-r = %d\n", tmp->rgb.r);
		// printf("     rgb-g = %d\n", tmp->rgb.g);
		// printf("     rgb-b = %d\n", tmp->rgb.b);
		// printf("     xyz-x = %f\n", tmp->xyz.x);
		// printf("     xyz-y = %f\n", tmp->xyz.y);
		// printf("     xyz-z = %f\n", tmp->xyz.z);
		// printf("  xyz_3d-x = %f\n", tmp->xyz_3d.x);
		// printf("  xyz_3d-y = %f\n", tmp->xyz_3d.y);
		// printf("  xyz_3d-z = %f\n", tmp->xyz_3d.z);
		// printf("       fov = %d\n", tmp->fov);
		// printf("       lbr = %f\n", tmp->lbr);
		// printf("        sd = %f\n", tmp->sd);
		// printf("        cd = %f\n", tmp->cd);
		// printf("        ch = %f\n", tmp->ch);
		// printf(      "next = %p\n", tmp->next);

		printf("--- Node %d end ---\n\n\n", i);
		tmp = tmp->next;
		i++;
	}
}


// void	ft_tuple_print(t_tuple *t)
// {
// 	if (!t)
// 	{
// 		printf("%sError: tuple is NULL%s\n", RED, ENDCLR);
// 		return ;
// 	}
// 	printf("x: %.3f | y: %.3f | z: %.3f | w: %.1f %s\n",
// 			t->x, t->y, t->z, t->w,
// 			t->w == 0 ? "(VECTOR)" : t->w == 1 ? "(POINT)" : "(neither)");
// }

// void	ft_print_line(char c)
// {
// 	int i;

// 	i = 0;
// 	while (i < 62)
// 	{
// 		write(1, &c, 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

//  void	print_y(char *s)
//  {
// 	printf("%s%s%s", YELLOW, s, ENDCLR);
//  }

//   void	print_r(char *s)
//  {
// 	printf("%s%s%s", RED, s, ENDCLR);
//  }

//  void	print_g(char *s)
//  {
// 	printf("%s%s%s", GREEN, s, ENDCLR);
//  }


// void	ft_colour_printer(t_colour *c)
// {
// 		if (!c)
// 	{
// 		printf("%sError: colour tuple is NULL%s\n", RED, ENDCLR);
// 		return ;
// 	}
// 	printf("r: %.3f | g: %.3f | b: %.3f\n", c->r, c->g, c->b);
// }