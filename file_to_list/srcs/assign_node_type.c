#include "../inc/file_to_list.h"

int move_past_type(t_list **l)
{
    t_list *current;

    current = *l;

    while (current)
    {
    if(current->type == ambiant)
        current->s = current->s + 1;
    else if(current->type == camera)
        current->s = current->s + 1;
    else if(current->type == light)
        current->s = current->s + 1;
    else if(current->type == plane)
        current->s = current->s + 2;
    else if(current->type == sphere)
        current->s = current->s + 2;
    else if(current->type == cylinder)
        current->s = current->s + 2;
    current->s = skip_space(current->s);
    current = current->next;
    }
    return (SUCCESS);
}

int	assign_node_type(t_list **l)
{
    t_list *current;

    current = *l;

    while (current)
    {
        if (!ft_strncmp(current->s, "A", 1))
            current->type = ambiant;
        else if (!ft_strncmp(current->s, "C", 1))
            current->type = camera;
        else if (!ft_strncmp(current->s, "L", 1))
            current->type = light;
        else if (!ft_strncmp(current->s, "pl", 2))
            current->type = plane;
        else if (!ft_strncmp(current->s, "sp", 2))
            current->type = sphere;
        else if (!ft_strncmp(current->s, "cy", 2))
            current->type = cylinder;
        //if none of these, return error? e.g. "yc" Should we add a final 'else' for that?
        current = current->next;
    }
    move_past_type(l);
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

