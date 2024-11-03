#include "../inc/file_to_list.h"

/*
[f], [f], [f]
2x commas
3x floats
*/

int process_xyz(t_list *current)
{
    printf("process xyz\n");

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
    return (ret_error(E_XYZ_CHARS, current));

// check for two commas
    if (!count_commas(sub_string, 2))
        return (ret_error(E_XYZ_COMMA, current));

// split into three strings?

// convert argument to float
    current->xyz.x = 2.4;
    current->xyz.y = 2.4;
    current->xyz.z = 2.4;
    // current-> alr = ft_atof(current->s);

// // check within range
//     if (current->alr < 0.0 || current->alr > 1.0)
//         return (ret_error(E_ALR_RANGE, current));

// move pointner past argument
    current->s = current->s + i;

// move pointer to next argument
    current->s = skip_space(current->s);
    // printf("data = %s\n", current->s);
free(sub_string);

return (E_SUCCESS);
}