#include "../inc/file_to_list.h"

//stupid way of printing the scene, .rt file has to have C, L, A, sp, sp, cy
static void scene_print(t_scene *scene)
{
	printf("\nParsed into scene:\n"
		" A: alr=%.3f, rgb=%.2f|%.2f|%.2f\n"
		" L: lbr=%.3f, xyz=%.2f|%.2f|%.2f\n"
		" C: focl=%f, xyz=%.2f|%.2f|%.2f\n"
		"sp: type=%d, sd=%.2f, xyz=%.2f|%.2f|%.2f, rgb=%.1f|%.1f|%.1f\n",
		// "sp: type=%d, sd=%.2f, xyz=%.2f|%.2f|%.2f, rgb=%.1f|%.1f|%.1f\n"
		// "cy: type=%d, xyz=%.2f|%.2f|%.2f, xyz3d=%.2f|%.2f|%.2f, cd=%.2f, ch=%.2f, rgb=%.1f|%.1f|%.1f\n",
		scene->ambiant.alr, scene->ambiant.rgb.r, scene->ambiant.rgb.g, scene->ambiant.rgb.b,
		scene->light.lbr, scene->light.xyz.x, scene->light.xyz.y, scene->light.xyz.z,
		scene->camera.focal_length, scene->camera.xyz.x, scene->camera.xyz.y, scene->camera.xyz.z,
		scene->shapes[0].type, scene->shapes[0].sd, scene->shapes[0].xyz.x, scene->shapes[0].xyz.y, scene->shapes[0].xyz.z,
			scene->shapes[0].rgb.r, scene->shapes[0].rgb.g, scene->shapes[0].rgb.b);
		// scene->shapes[1].type, scene->shapes[1].sd, scene->shapes[1].xyz.x, scene->shapes[1].xyz.y, scene->shapes[1].xyz.z,
		// 	scene->shapes[1].rgb.r, scene->shapes[1].rgb.g, scene->shapes[1].rgb.b,
		// scene->shapes[2].type, scene->shapes[2].xyz.x, scene->shapes[2].xyz.y, scene->shapes[2].xyz.z,
		// 	scene->shapes[2].xyz3d.x, scene->shapes[2].xyz3d.y, scene->shapes[2].xyz3d.z,
		// 	scene->shapes[2].cd, scene->shapes[2].ch, scene->shapes[2].rgb.r, scene->shapes[2].rgb.g, scene->shapes[2].rgb.b);
}

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

	//initialize mlx
	mlx = mlx_init(WINSIZE, WINSIZE, "minirt", false);
	if (!(mlx))
		return (free(scene), ERROR);
	img = mlx_new_image(mlx, WINSIZE, WINSIZE);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (free(scene), mlx_terminate(mlx), ERROR);
	
	//render scene
	scene_print(scene);
	// if (render_pixels(img, scene) == ERROR)
	// 	return (mlx_terminate(mlx), ERROR);

	//mlx hooks and cleanup
	mlx_key_hook(mlx, &esc_keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return(free(scene), SUCCESS);
}
