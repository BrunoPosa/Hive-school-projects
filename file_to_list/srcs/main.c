#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

void	init_node(l)
{
	l->s = "can we init like this?";
	l->type = 0;
	l->alr = 4.2;
	l->rgb->r = 4.2;
	l->rgb->g = 4.2;
	l->rgb->b = 4.2;
	l->xyz->x = 4.2;
	l->xyz->y = 4.2;
	l->xyz->z = 4.2;
	l->xyz_3d->x = 4.2;
	l->xyz_3d->y = 4.2;
	l->xyz_3d->z = 4.2;
	l->fov = 42;
	l->lbr = 4.2;
	l->sd = 4.2;
	l->cd = 4.2;
	l->ch = 4.2;
	l->next = NULL;
}


int	main(int argc, char **argv)
{
	t_list *l = NULL;

	if (argc != 2)
	{
		printf("Error: no file given\n"); // not correct if there were 3 file names
		return (1);
	}

	init_node(l);

	if (does_file_end_with_rt(argv[1]) == 0)
	{
		printf("Error: file does not end with .rt\n");
		return (ERROR);
	}

	file_to_list(argv[1], &l);
	process_list(&l);
	// validate: checkif there are two camera, if camera >1 retuirn erroro
	// assign_scene_object(l);

	ft_list_print(&l);
	//    free()
	return (0);
}

