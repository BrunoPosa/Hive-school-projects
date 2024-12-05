#include "../inc/file_to_list.h"


int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;

	mlx = NULL;
	img = NULL;
	//allocate scene
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (ret_error(E_MALLOC, NULL));

	//parse file into scene
	if (parse(argc, argv, scene) != SUCCESS)
		return (free(scene), ERROR);
	// scene_print(scene);

	//initialize mlx
	mlx = mlx_init(WINSIZE, WINSIZE, "minirt", false);
	if (!(mlx))
		return (free(scene), ERROR);
	img = mlx_new_image(mlx, WINSIZE, WINSIZE);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (free(scene), mlx_terminate(mlx), ERROR);

	//render scene
	if (render_pixels(scene, img) != SUCCESS)
		return (mlx_terminate(mlx), ERROR);

	//mlx hooks and cleanup
	mlx_key_hook(mlx, &esc_keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return(free(scene), SUCCESS);
}
