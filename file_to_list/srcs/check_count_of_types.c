#include "../inc/file_to_list.h"

void    check_count_of_types(t_list **l)
{
    t_list *current = *l;
    int count_camera = 0;
    int count_cylinder = 0;
    int count_plane = 0;
    int count_light = 0;
    int count_sphere = 0;
    int count_ambiant = 0;

    while (current)
    {
        if (current->type == camera)
            count_camera++;
        else if (current->type == cylinder)
            count_cylinder++;
        else if (current->type == plane)
            count_plane++;
        else if (current->type == light)
            count_light++;
        else if (current->type == sphere)
            count_sphere++;
        else if (current->type == ambiant)
            count_ambiant++;
        current = current->next;
    }
    printf("\n\n\n");
    printf("count_camera = %d\n", count_camera);
    printf("count_cylinder = %d\n", count_cylinder);
    printf("count_plane = %d\n", count_plane);
    printf("count_light = %d\n", count_light);
    printf("count_sphere = %d\n", count_sphere);
    printf("count_ambiant = %d\n", count_ambiant);
}