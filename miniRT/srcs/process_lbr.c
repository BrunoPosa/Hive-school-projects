#include "../inc/file_to_list.h"


// needs to be between 0.0. and 1.0
int process_lbr(t_list *current)
{
	// printf("process lbr\n");

	int i;
	int	atoi_overflow;
	char *sub_string;

// find len until space
	i = len_until_space(current->p);
// printf("LEN UNITL SPACE = %d\n", i);
	atoi_overflow = 0;
// iscolate argument
	sub_string = ft_substr(current->p, 0, i);
	if (sub_string == NULL)
		return (ret_error(E_MALLOC, current));
	// printf("substring = %s\n", sub_string);


// check if only legal chars
	if(!only_legal_chars(sub_string, LEGAL_CHARS4) || !is_n_valid(sub_string))
		return (free(sub_string), ret_error(E_ALR_CHARS, current));

// convert argument to float and check if it's in range
	current->lbr = ft_atod(current->p, &atoi_overflow);
	if (current->lbr < 0 || current->lbr > 1 || atoi_overflow)
		return (free(sub_string), ret_error(E_ALR_RANGE, current));
// printf("lbr=%lf\n", current->lbr);
// move pointner past argument
	current->p = current->p + i;

// move pointer to next argument
	current->p = skip_space(current->p);
	// printf("data = %s\n", current->p);
free(sub_string);

// this is the same as lbr
return (E_SUCCESS);
}
