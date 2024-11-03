#include "../inc/file_to_list.h"

/*
find_len_until_space()
int	only_legal_chars(char *s, char *LEGAL_CHARS4)

[0-255], [0-255], [0-255]

minimum = 0
maximum = 255
3x unsigned ints
2x commas
max 3 digits
only allowed characters are numbers and commas


*/


int process_rgb(t_list *current)
{
    printf("process rgb\n");

    int i;
    char *sub_string;

// find len until space
    i = len_until_space(current->s);
// printf("LEN UNITL SPACE = %d\n", i);

// iscolate argument
    sub_string = ft_substr(current->s, 0, i);
    printf("substring = %s\n", sub_string);


// check if only legal chars !!!!SEGFAULT HERE!!!!
//   if(!only_legal_chars(sub_string, LEGAL_CHARS4))
//     return (ret_error(E_RGB_CHARS, current));

// // check for two commas
    if (!count_commas(sub_string, 2))
        return (ret_error(E_RGB_COMMA, current));

// split into three strings?
// // split into three strings?
//     char **vec = ft_split(sub_string, ',');
//     if (!vec)
//         return (ret_error(E_SPLIT, current));   
// 	current->rgb.r = ft_atof(vec[0]);
// 	current->rgb.g = ft_atof(vec[1]);
// 	current->rgb.b = ft_atof(vec[2]);
// 	free_arr(vec);


// convert argument to 3x ints
    current->rgb.r = 24;
    current->rgb.g = 24;
    current->rgb.b = 24;

// // // check within range
//     if (current->rgb.r < 0 || current->rgb.b > 255)
//         return (ret_error(E_RGB_RANGE, current));
//     if (current->rgb.g < 0 || current->rgb.b > 255)
//         return (ret_error(E_RGB_RANGE, current));
//     if (current->rgb.b < 0 || current->rgb.b > 255)
//         return (ret_error(E_RGB_RANGE, current));

printf("rgb = %d, %d, %d\n", current->rgb.r, current->rgb.g, current->rgb.b);
// move pointner past argument
    current->s = current->s + i;

// move pointer to next argument
    current->s = skip_space(current->s);
    // printf("data = %s\n", current->s);
free(sub_string);

return (E_SUCCESS);
}