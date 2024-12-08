#include "../inc/file_to_list.h"

void	ft_scene_print(t_scene *scene)
{
	printf("spheres = %d\n", scene->n_sphere);
}

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
		printf("       p = %s\n", tmp->p);
		printf("      type = %d\n", tmp->type);
		printf("       alr = %f\n", tmp->alr);
		printf("     rgb-r = %f\n", tmp->rgb.r);
		printf("     rgb-g = %f\n", tmp->rgb.g);
		printf("     rgb-b = %f\n", tmp->rgb.b);
		printf("     xyz-x = %f\n", tmp->xyz.x);
		printf("     xyz-y = %f\n", tmp->xyz.y);
		printf("     xyz-z = %f\n", tmp->xyz.z);
		printf("  xyz_3d-x = %f\n", tmp->xyz_3d.x);
		printf("  xyz_3d-y = %f\n", tmp->xyz_3d.y);
		printf("  xyz_3d-z = %f\n", tmp->xyz_3d.z);
		printf("       fov = %d\n", tmp->fov);
		printf("       lbr = %f\n", tmp->lbr);
		printf("        sd = %f\n", tmp->sd);
		printf("        cd = %f\n", tmp->cd);
		printf("        ch = %f\n", tmp->ch);
		printf(      "next = %p\n", tmp->next);

		printf("--- Node %d end ---\n\n\n", i);
		tmp = tmp->next;
		i++;
	}
}


void	ft_vec_print(t_vec t)
{
	printf("x: %.3f | y: %.3f | z: %.3f\n",
			t.x, t.y, t.z);
}


//  void	print_y(char *s)
//  {
// 	printf("%s%s%s", YELLOW, s, ENDCLR);
//  }


void	ft_colour_printer(t_colour *c)
{
		if (!c)
	{
		printf("%sError: colour tuple is NULL%s\n", RED, ENDCLR);
		return ;
	}
	printf("r: %.3f | g: %.3f | b: %.3f\n", c->r, c->g, c->b);
}


// //stupid way of printing the scene, .rt file has to have C, L, A, sp, sp, cy
// void scene_print(t_scene *scene)
// {
// 	printf("\nParsed into scene:\n"
// 		" A: rgb=%.2f|%.2f|%.2f\n"
// 		" L: lbr=%.3f, xyz=%.2f|%.2f|%.2f\n"
// 		" C: focl=%f, xyz=%.2f|%.2f|%.2f\n"
// 		"sp: type=%d, sd=%.2f, xyz=%.2f|%.2f|%.2f, rgb=%.1f|%.1f|%.1f\n",
// 		// "sp: type=%d, sd=%.2f, xyz=%.2f|%.2f|%.2f, rgb=%.1f|%.1f|%.1f\n"
// 		// "cy: type=%d, xyz=%.2f|%.2f|%.2f, xyz3d=%.2f|%.2f|%.2f, cd=%.2f, ch=%.2f, rgb=%.1f|%.1f|%.1f\n",
// 		scene->ambiant.r, scene->ambiant.g, scene->ambiant.b,
// 		scene->light.lbr, scene->light.xyz.x, scene->light.xyz.y, scene->light.xyz.z,
// 		scene->camera.focal_length, scene->camera.xyz.x, scene->camera.xyz.y, scene->camera.xyz.z,
// 		scene->shapes[0].type, scene->shapes[0].sd, scene->shapes[0].xyz.x, scene->shapes[0].xyz.y, scene->shapes[0].xyz.z,
// 			scene->shapes[0].rgb.r, scene->shapes[0].rgb.g, scene->shapes[0].rgb.b);
// 		// scene->shapes[1].type, scene->shapes[1].sd, scene->shapes[1].xyz.x, scene->shapes[1].xyz.y, scene->shapes[1].xyz.z,
// 		// 	scene->shapes[1].rgb.r, scene->shapes[1].rgb.g, scene->shapes[1].rgb.b,
// 		// scene->shapes[2].type, scene->shapes[2].xyz.x, scene->shapes[2].xyz.y, scene->shapes[2].xyz.z,
// 		// 	scene->shapes[2].xyz3d.x, scene->shapes[2].xyz3d.y, scene->shapes[2].xyz3d.z,
// 		// 	scene->shapes[2].cd, scene->shapes[2].ch, scene->shapes[2].rgb.r, scene->shapes[2].rgb.g, scene->shapes[2].rgb.b);
// }
