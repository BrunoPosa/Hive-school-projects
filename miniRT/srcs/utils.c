#include "../inc/file_to_list.h"
#include <math.h>

char    *skip_space(char *s)
{
	if (!s)
		return (NULL);
	while(*s && *s == ' ')
			s++;
	return (s);
}

int	does_file_end_with_rt(char *filename)
{
	int len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	if (ft_strncmp(&filename[len - 3], ".rt", 3))
		return (0);
	return (1);
}

void	esc_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(param);
	(void)param;
}

float	calculate_focal_len(unsigned int fov)
{
	float focal_len;
	float fov_radians;

	// Convert FOV from degrees to radians
	fov_radians = (fov * M_PI) / 180.0;

	// Calculate the focal length using half of the FOV in radians
	focal_len = (WRLD_WINWIDTH / 2.0) / tan(fov_radians / 2.0);
	return focal_len;
}
