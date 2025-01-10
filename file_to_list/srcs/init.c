#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

void	init_node(t_list **l)
{
 	// (*l)->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	// (*l)->xyz = (t_xyz *)malloc(sizeof(t_xyz));
	// (*l)->xyz_3d = (t_xyz_3d *)malloc(sizeof(t_xyz_3d));
	// // calloc?

	(*l)->s = "can we init like this?";
	(*l)->type = 0;
	(*l)->alr = 4.2;
	(*l)->rgb.r = 42;
	(*l)->rgb.g = 42;
	(*l)->rgb.b = 42;
	(*l)->xyz.x = 4.2;
	(*l)->xyz.y = 4.2;
	(*l)->xyz.z = 4.2;
	(*l)->xyz_3d.x = 4.2;
	(*l)->xyz_3d.y = 4.2;
	(*l)->xyz_3d.z = 4.2;
	(*l)->fov = 42;
	(*l)->lbr = 4.2;
	(*l)->sd = 4.2;
	(*l)->cd = 4.2;
	(*l)->ch = 4.2;
	(*l)->next = NULL;
}