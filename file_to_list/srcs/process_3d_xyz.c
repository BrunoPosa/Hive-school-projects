#include "../inc/file_to_list.h"

/*
[-1,1], [-1,1], [-1,1]

minimum = -1
maximum = 1
3x floats
2x commas
*/

int process_xyz_3d(t_list *current)
{
    printf("process xyz_3d\n");

    int i;
    char *sub_string;

// find len until space
    i = len_until_space(current->s);
// printf("LEN UNITL SPACE = %d\n", i);

// iscolate argument
    sub_string = ft_substr(current->s, 0, i);
    printf("substring = %s\n", sub_string);


// check if only legal chars
  if(!only_legal_chars(sub_string, LEGAL_CHARS3))
    return (ret_error(E_XYZ_3D_CHARS, current));

// check for two commas
    if (!count_commas(sub_string, 2))
        return (ret_error(E_XYZ_3D_COMMA, current));

// // split into three strings?
//     char **vec = ft_split(sub_string, ',');
//     if (!vec)
//         return (ret_error(E_SPLIT, current));   
// 	current->xyz_3d.x = ft_atof(vec[0]);
// 	current->xyz_3d.y = ft_atof(vec[1]);
// 	current->xyz_3d.z = ft_atof(vec[2]);
// 	free_arr(vec);

// convert argument to float
    current->xyz_3d.x = 2.4;
    current->xyz_3d.y = 2.4;
    current->xyz_3d.z = 2.4;

// // check within range


// move pointner past argument
    current->s = current->s + i;

// move pointer to next argument
    current->s = skip_space(current->s);
    // printf("data = %s\n", current->s);
free(sub_string);

return (E_SUCCESS);
}