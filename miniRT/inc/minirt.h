#include "./file_to_list.h"

typedef stuct s_rt
{
    mlx_t *mlx;
    mlx_image_t *img;

    float aspect_ratio;

    t_list light;
    t_list camera;
    t_list ambiant;

    t_list *cylinder;
    t_list *plane;
    t_list *sphere;

    int n_cylinder;
    int n_sphere;
    int n_plane

    int width;
    int height;

    t_error error;
} t_rt;


