#include "../inc/file_to_list.h"
// needs to be between 0.0. and 1.0
int process_alr(t_list *current)
{
	printf("process alr\n");

	int i;
	int	atoi_overflow;
	char *sub_string;

// find len until space
	i = len_until_space(current->s);
// printf("LEN UNITL SPACE = %d\n", i);
	atoi_overflow = 0;
// iscolate argument
	sub_string = ft_substr(current->s, 0, i);
	if (sub_string == NULL)
		return (ret_error(E_MALLOC, current));
	printf("substring = %s\n", sub_string);


// check if only legal chars
	if(!only_legal_chars(sub_string, LEGAL_CHARS4) || !is_number_valid(sub_string))
		return (free(sub_string), ret_error(E_ALR_CHARS, current));

// convert argument to float and check if it's in range
	current->alr = ft_atod(current->s, &atoi_overflow);
	if (current->alr < 0 || current->alr > 1 || atoi_overflow)
		return (free(sub_string), ret_error(E_ALR_RANGE, current));

// move pointner past argument
	current->s = current->s + i;

// move pointer to next argument
	current->s = skip_space(current->s);
	// printf("data = %s\n", current->s);
free(sub_string);

// this is the same as lbr
return (E_SUCCESS);
}