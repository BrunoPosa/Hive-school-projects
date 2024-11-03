#include "../inc/file_to_list.h"

/*
if it allows negative, that means it is not there
float

same as sd, cd, ch
*/

int process_cd(t_list *current)
{
    printf("process cd\n");

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
    return (ret_error(E_FLOAT_CHARS, current));

// convert argument to float
    current->cd = 2.4;
    // current-> cd = ft_atof(current->s);

// // check within range
//     if (current->cd < 0.0 || current->cd > 1.0)
//         return (ret_error(E_ALR_RANGE, current));

// move pointner past argument
    current->s = current->s + i;

// move pointer to next argument
    current->s = skip_space(current->s);
    // printf("data = %s\n", current->s);
free(sub_string);

return (E_SUCCESS);
}