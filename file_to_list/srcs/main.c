#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

int	main(int argc, char **argv)
{
	t_list *l = NULL;

	if (argc != 2)
	{
		printf("Error: no file given\n");
		return (1);
	}

	//input the file
	file_to_list(argv[1], &l);
	process_list(&l);
	// validate: checkif there are two camera, if camera >1 retuirn erroro
	// assign_scene_object(l);

	ft_list_print(&l);
	//    free()
	return (0);
}

