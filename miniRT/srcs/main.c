#include "../inc/file_to_list.h"
#include "../../libft/libft.h"
#include "../inc/minirt.h"

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
		return (ret_error(E_MALLOC, l));

	if (process_list(&l) == ERROR)
	{
		printf("======================== FILE VALIDATION FAILED ========================");
		return (-1);
	}
	// validate: checkif there are two camera, if camera >1 retuirn erroro
	// assign_scene_object(l);

	t_rt rt; // this is for our general program info

	check_count_of_types(l, &rt); // analyse the linked list and store those values in the general program info


	// init_camera(&rt); 	// camera calculations
	init_mlx(&rt);		// mlx general setup
	// render_scene(&rt);	// render scene
	//  mlx_loop(rt.mlx->mlx); // mlx loop

	ft_list_print(&l);
	// free_all(&l); // l is a linked list, that holds input data,
	// and rt holds env data?

	return (0);
}

