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
	int	atoi_overflow;
	char **xyz;

	xyz = NULL;
	atoi_overflow = 0;
// find len until space
	i = len_until_space(current->s);
// printf("LEN UNITL SPACE = %d\n", i);

// iscolate argument
	sub_string = ft_substr(current->s, 0, i);
	printf("substring =%s\n", sub_string);


// check if only legal chars
	if(!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (free(sub_string), ret_error(E_XYZ_CHARS, current));
// check for two commas
	if (count_commas_between(sub_string) != 2)
		return (free(sub_string), ret_error(E_XYZ_COMMA, current));

// split into three strings
    xyz = ft_split(sub_string, ',');
	if (!xyz)
		return (free(sub_string), ret_error(E_SPLIT, current));
	if (!is_number_valid(xyz[0]) || !is_number_valid(xyz[1]) || !is_number_valid(xyz[2]))
		return (free(sub_string), ret_error(E_XYZ_CHARS, current));
	current->xyz.x = ft_atod(xyz[0], &atoi_overflow);
	current->xyz.y = ft_atod(xyz[1], &atoi_overflow);
	current->xyz.z = ft_atod(xyz[2], &atoi_overflow);
	free_array(xyz);

// check within range
    if (atoi_overflow)
        return (free(sub_string), ret_error(E_XYZ_RANGE, current));
printf("	current->xyz.x = %lf\n", current->xyz.x);
printf("	current->xyz.y = %lf\n", current->xyz.y);
printf("	current->xyz.z = %lf\n", current->xyz.z);
// move pointner past argument
	current->s = current->s + i;

// move pointer to next argument
	current->s = skip_space(current->s);
	// printf("data = %s\n", current->s);
free(sub_string);

return (E_SUCCESS);
}