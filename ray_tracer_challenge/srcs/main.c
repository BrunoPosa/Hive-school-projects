#include "../inc/ray_tracer.h"

int	main(void)
{
	ft_print_line('#');
	printf("Test\n\n");

	// tests_tuples();
	// tests_colours();
	// tests_canvas();

	/*  P R O J E C T I L E  */
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx = mlx_init(WINSIZE, WINSIZE, "projectile", false);
	if (!(mlx))
		return (ERROR);
	img = mlx_new_image(mlx, WINSIZE, WINSIZE);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (mlx_terminate(mlx), ERROR);
	project_one(img);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (0);
}

