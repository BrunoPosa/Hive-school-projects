#include "../inc/file_to_list.h"
#include "../../MLX42/include/MLX42/MLX42.h"


static void scene_print(t_scene *scene)
{
	printf("", scene->ambiant->alr);

}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;

	mlx = NULL;
	img = NULL;
	scene = NULL;
	if (parse(argc, argv, scene) != SUCCESS)
		return (free(scene), ERROR);
	mlx = mlx_init(WINSIZE, WINSIZE, "minirt", false);
	if (!(mlx))
		return (ERROR);
	img = mlx_new_image(mlx, WINSIZE, WINSIZE);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (mlx_terminate(mlx), ERROR);

	scene_print(scene);

	// if (render_pixels(img, scene) == ERROR)
	// 	return (mlx_terminate(mlx), ERROR);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return(SUCCESS);
}
