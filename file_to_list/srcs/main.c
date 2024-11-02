#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

int	main(int argc, char **argv)
{
	t_list		*l;
	// t_error		exit_code;

	l = NULL;

	// if (argc != 2)
	// {
	// 	printf("Useful Error message\n"); // not correct if there were 3 file names
	// 	return (1);
	// }

// >>>> if GNL returns \n, skip it


	if (argc != 2)
		return(ret_error(E_ARGS, NULL));

	if (does_file_end_with_rt(argv[1]) == 0)
		return(ret_error(E_FILE_NAME, NULL));

	if (file_to_list(argv[1], &l))
		return (ret_error(E_ILLEGAL_CHARS1, l));

	process_list(&l);
	// validate: checkif there are two camera, if camera >1 retuirn erroro
	// assign_scene_object(l);

	ft_list_print(&l);
	//    free()
	return (0);
}

