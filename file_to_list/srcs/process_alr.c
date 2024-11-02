#include "../inc/file_to_list.h"

void process_alr(t_list *current)
{
    printf("process alr\n");

    int i;

// find len until space
    i = len_until_space(current->s);
    // printf("LEN UNITL SPACE = %d\n", i);


// if(only_legal_chars_n(current->s, LEGAL_CHARS4, i))
//     return (ret_error(E_ILLEGAL_CHARS4, current));

// we only want to atof string until space
// is that substr??



   printf("data = %s\n", current->s);
    current->s = current->s + i;
    //change this!!
    current->alr = 2.4;

    current->s = skip_space(current->s);
    printf("data = %s\n", current->s);

    // current->alr = ft_atof(current->s);

    // alr - 0.0 - 1.0
    // skip_space(current->s);
    // rgb - [0-255], [0-255], [0-255]
    // skip_space(current->s);
    // ft_anything_else_in_string_say_no(current->s);


//  0.0 - 1.0

// float between zero and 1

// this is the same as lbr

}