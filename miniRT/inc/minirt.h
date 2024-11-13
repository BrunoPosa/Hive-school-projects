#include "./file_to_list.h"


// // general program info
// typedef stuct s_rt
// {
//     mlx_t *mlx;
//     mlx_image_t *img;

//     int width;
//     int height;
//     float aspect_ratio;

// // all of these items are in a linked list already
// // we check that there is only one of eaech these three
//     t_list light;
//     t_list camera;
//     t_list ambiant;

// // can we use a link2 to connect objects of the same type?
// // then to free we can rip through all the linked list,
// // or another way would be to reconnect the nodes to new linked lists
//     t_list *cylinder;
//     t_list *plane;
//     t_list *sphere;

//     int n_cylinder;
//     int n_sphere;
//     int n_plane



// } t_rt;


// // render struct for information of the pixel to be rendered
// typedef struct s_render
// {
// 	t_vec	color;
// 	int		rgba;
// 	int		x;
// 	int		y;
// 	t_vec	px_center;
// 	t_vec	ray_direction;
// 	t_ray	ray;
// }	t_render;

/// free all the memory allocated for the rt struct
void free_rt(t_rt *rt);