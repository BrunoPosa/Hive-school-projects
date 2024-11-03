#include "../inc/file_to_list.h"

int process_alr(t_list *current)
{
    printf("process alr\n");

    int i;
    char *sub_string;

// find len until space
    i = len_until_space(current->s);
// printf("LEN UNITL SPACE = %d\n", i);

// iscolate argument
    sub_string = ft_substr(current->s, 0, i);
    printf("substring = %s\n", sub_string);


// check if only legal chars
  if(!only_legal_chars(sub_string, LEGAL_CHARS4))
    return (ret_error(E_ALR_CHARS, current));

// convert argument to float
    current->alr = 2.4;
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
//  0.0 - 1.0

// float between zero and 1

// this is the same as lbr
return (E_SUCCESS);
}