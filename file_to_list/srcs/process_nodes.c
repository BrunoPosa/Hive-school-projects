#include "../inc/file_to_list.h"

// ONE OF THESE HAS OPTIONAL ARGUMENTS!!!!

void process_ambiant(t_list *current)
{
    printf("process ambiant\n");
    printf("data = %s\n", current->s);
    // alr - 0.0 - 1.0
    // skip_space(current->s);
    // rgb - [0-255], [0-255], [0-255]
    // skip_space(current->s);
    // ft_anything_else_in_string_say_no(current->s);
}

void process_camera(t_list *current)
{
    printf("process camera\n");
     printf("data = %s\n", current->s);
    // xyz - [f], [f], [f]
    // skip_space(current->s);
    // fov - [0-180]
    // skip_space(current->s);
    // xyz_3d - [-1,1], [-1,1], [-1,1]
    // skip_space(current->s);
    // ft_anything_else_in_string_say_no(current->s);
}
void process_cylinder(t_list *current)
{
    printf("process cylinder\n");
     printf("data = %s\n", current->s);
    // xyz - [f], [f], [f]
    // skip_space(current->s);
    // xyz_3d - [-1,1], [-1,1], [-1,1]
    // skip_space(current->s);
    // cd - [0-1]
    // skip_space(current->s);
    // ch - [0-1]
    // skip_space(current->s);
    // rgb - [0-255], [0-255], [0-255]
    // ft_anything_else_in_string_say_no(current->s);
}

void process_plane(t_list *current)
{
    printf("process plane\n");
     printf("data = %s\n", current->s);
    // xyz - [f], [f], [f]
    // skip_space(current->s);
    // xyz_3d - [-1,1], [-1,1], [-1,1]
    // skip_space(current->s);
    // rgb - [0-255], [0-255], [0-255]
    // ft_anything_else_in_string_say_no(current->s);
}

void process_light(t_list *current)
{
    printf("process light\n");
     printf("data = %s\n", current->s);
    // xyz - [f], [f], [f]
    // skip_space(current->s);
    // lbr - [0-1]
    // skip_space(current->s);
    // rgb - [0-255], [0-255], [0-255]
    // ft_anything_else_in_string_say_no(current->s);
}

void process_sphere(t_list *current)
{
    printf("process sphere\n");
     printf("data = %s\n", current->s);
    // xyz - [f], [f], [f]
    // skip_space(current->s);
    // sd - [f]
    // skip_space(current->s);
    // rgb - [0-255], [0-255], [0-255]
    // ft_anything_else_in_string_say_no(current->s);
}

void process_node(t_list *current)
{
    if (current->type == ambiant)
    {
        printf("we have an ambiant\n");
        process_ambiant(current);
    }
    else if (current->type == camera)
    {
        printf("we have a camera\n");
        process_camera(current);
    }
    else if (current->type == light)
    {
        printf("we have a light\n");
        process_light(current);
    }
    else if (current->type == plane)
    {
        printf("we have a plane\n");
        process_plane(current);
    }
    else if (current->type == sphere)
    {
        printf("we have a sphere\n");
        process_sphere(current);
    }
    else if (current->type == cylinder)
    {
        printf("we have a cylinder\n");
        process_cylinder(current);
    }
    else
    {
        printf("Error: has a blank line slipped through??\n\n");
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