#include "../inc/file_to_list.h"

int	assign_node_type(t_list **l)
{
    t_list *current;

    current = *l;

    while (current)
    {
        // printf("%d\n", current->type);
        if (!ft_strncmp(current->s, "A", 1))
        {
            current->type = ambiant;
        }
        else if (!ft_strncmp(current->s, "C", 1))
        {
            current->type = camera;
        }
        else if (!ft_strncmp(current->s, "L", 1))
        {
            current->type = light;
        }
        else if (!ft_strncmp(current->s, "pl", 2))
        {
            current->type = plane;
        }
        else if (!ft_strncmp(current->s, "sp", 2))
        {
            current->type = sphere;
        }

        else if (!ft_strncmp(current->s, "cy", 2))
        {
            current->type = cylinder;
        }
        //s else
        //  s   return (ERROR);
        printf("%d\n", current->type);
        current = current->next;
    }
    return (SUCCESS);
}


// if current->s[0] == num, ',' 
//     return error


// if (!strcmp(current->s[0] && !strcmp(s[1] == ' '))



// A
// C
// L
// pl
// sp
// cy

// check the first letters of current->s are etc.

// update the pointer, of the s.

// update the type enum.

