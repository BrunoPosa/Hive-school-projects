#include "../inc/file_to_list.h"


static void scene_print(t_scene *scene)
{
	printf("\nParsed into scene:\n"
		"A: alr=%.3f, rgb=%.f|%.f|%.f\n"
		"L: lbr=%.3f, xyz=%.f|%.f|%.f\n"
		"C: fov=%d, xyz=%.f|%.f|%.f\n",
		scene->ambiant->alr, scene->ambiant->rgb.r, scene->ambiant->rgb.g, scene->ambiant->rgb.b,
		scene->light->lbr, scene->light->xyz.x, scene->light->xyz.y, scene->light->xyz.z,
		scene->camera->fov, scene->camera->xyz.x, scene->camera->xyz.y, scene->camera->xyz.z);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;

	mlx = NULL;
	img = NULL;
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (ret_error(E_MALLOC, NULL));
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
