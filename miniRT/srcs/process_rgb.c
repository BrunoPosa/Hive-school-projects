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
	// printf("process rgb\n");

	int i;
	int	atoi_overflow;
	char *sub_string;
	char **rgb;

	rgb = NULL;
	atoi_overflow = 0;
// find len until space
	i = len_until_space(current->p);
// printf("LEN UNITL SPACE = %d\n", i);

// iscolate argument
// printf("current->p = %s\n", current->p);
	sub_string = ft_substr(current->p, 0, i);
	if (sub_string == NULL)
		return (ret_error(E_MALLOC, current));
	// printf("substring = %s\n", sub_string);

// check if only legal chars !!!!SEGFAULT HERE!!!!
	if(!only_legal_chars(sub_string, LEGAL_CHARS5))
		return (free(sub_string), ret_error(E_RGB_CHARS, current));

// // check for two commas
	if (count_commas_between(sub_string) != 2)
		return (free(sub_string), ret_error(E_RGB_COMMA, current));

// split into three strings?
	rgb = ft_split(sub_string, ',');
	if (!rgb)
		return (free(sub_string), ret_error(E_SPLIT, current));
	current->rgb.r = ft_atoi(rgb[0], &atoi_overflow);
	current->rgb.g = ft_atoi(rgb[1], &atoi_overflow);
	current->rgb.b = ft_atoi(rgb[2], &atoi_overflow);
	free_array(rgb);


// check within range
	if (atoi_overflow
		|| current->rgb.r < 0 || current->rgb.r > 255
		|| current->rgb.g < 0 || current->rgb.g > 255
		|| current->rgb.b < 0 || current->rgb.b > 255)
		return (free(sub_string), ret_error(E_RGB_RANGE, current));
// printf("parsed rgb ints= %d, %d, %d\n", current->rgb.r, current->rgb.g, current->rgb.b);
// move pointner past argument
	current->p = current->p + i;

// move pointer to next argument
	current->p = skip_space(current->p);
	// printf("data = %s\n", current->p);
free(sub_string);

return (E_SUCCESS);
}