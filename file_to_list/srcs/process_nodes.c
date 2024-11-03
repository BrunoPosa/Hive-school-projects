#include "../inc/file_to_list.h"

// ONE OF THESE HAS OPTIONAL ARGUMENTS!!!!

void process_ambiant(t_list *current)
{
    printf("\nPROCESS AMBIANT\n");
    printf("data = %s\n", current->s);

    // alr - 0.0 - 1.0
    process_alr(current);

    // rgb - [0-255], [0-255], [0-255]
    process_rgb(current);

    // ft_anything_else_in_string_say_no(current->s);
}

void process_camera(t_list *current)
{
    printf("\nPROCESS CAMERA\n");
    printf("data = %s\n", current->s);

    // xyz - [f], [f], [f]
    process_xyz(current);

    // xyz_3d - [-1,1], [-1,1], [-1,1]
    process_xyz_3d(current);

    // fov - [0-180]
    process_fov(current);




    // ft_anything_else_in_string_say_no(current->s);
}
void process_cylinder(t_list *current)
{
    printf("\nPROCESS CYLINDER\n");
     printf("data = %s\n", current->s);

    // xyz - [f], [f], [f]
    process_xyz(current);

    // xyz_3d - [-1,1], [-1,1], [-1,1]
    process_xyz_3d(current);

    // cd - [f]
    process_cd(current);

    // ch - [f]
    process_ch(current);

    // rgb - [0-255], [0-255], [0-255]
    process_rgb(current);

    // ft_anything_else_in_string_say_no(current->s);
}

void process_plane(t_list *current)
{
    printf("\nPROCESS PLANE\n");
    printf("data = %s\n", current->s);

    // xyz - [f], [f], [f]
    process_xyz(current);

    // xyz_3d - [-1,1], [-1,1], [-1,1]
    process_xyz_3d(current);

    // rgb - [0-255], [0-255], [0-255]
    process_rgb(current);

    // ft_anything_else_in_string_say_no(current->s);
}

void process_light(t_list *current)
{
    printf("\nPROCESS LIGHT\n");
    printf("data = %s\n", current->s);

    // xyz - [f], [f], [f]
    process_xyz(current);

    // lbr - [0-1]
    process_lbr(current);

    // rgb - [0-255], [0-255], [0-255]
    process_rgb(current);

    // ft_anything_else_in_string_say_no(current->s);
}

void process_sphere(t_list *current)
{
    printf("\nPROCESS SHPERE\n");
    printf("data = %s\n", current->s);

    // xyz - [f], [f], [f]
    process_xyz(current);

    // sd - [f]
    process_sd(current);

    // rgb - [0-255], [0-255], [0-255]
    process_rgb(current);

    // ft_anything_else_in_string_say_no(current->s);
}

void process_node(t_list *current)
{
    if (current->type == ambiant)
    {
        printf("\n>> we have an ambiant\n");
        process_ambiant(current);
    }
    else if (current->type == camera)
    {
        printf("\n>> we have a camera\n");
        process_camera(current);
    }
    else if (current->type == light)
    {
        printf("\n>> we have a light\n");
        process_light(current);
    }
    else if (current->type == plane)
    {
        printf("\n>> we have a plane\n");
        process_plane(current);
    }
    else if (current->type == sphere)
    {
        printf("\n>> we have a sphere\n");
        process_sphere(current);
    }
    else if (current->type == cylinder)
    {
        printf("\n>> we have a cylinder\n");
        process_cylinder(current);
    }
    else
    {
        printf("\n\n>> Error: has a blank line slipped through??\n\n");
    }
}


void process_nodes(t_list **l)
{
	t_list *current = *l;

    while (current)
	{
		process_node(current);
		current = current->next;
	}
}