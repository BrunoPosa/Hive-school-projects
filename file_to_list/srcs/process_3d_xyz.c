#include "../inc/file_to_list.h"

/*
[-1,1], [-1,1], [-1,1]

minimum = -1
maximum = 1
3x floats
2x commas
*/

int	process_xyz_3d(t_list *current)
{
	printf("process xyz_3d\n");
	int		i;
	char	**xyz;
	char	*sub_string;
	int		atoi_overflow;

	xyz = NULL;
	atoi_overflow = 0;
// find len until space
	i = len_until_space(current->s);
// printf("LEN UNITL SPACE = %d\n", i);

// iscolate argument
	sub_string = ft_substr(current->s, 0, i);
	printf("substring = %s\n", sub_string);


// check if only legal chars
	if(!only_legal_chars(sub_string, LEGAL_CHARS3))
		return (free(sub_string), ret_error(E_XYZ_3D_CHARS, current));

// check for two commas
	if (count_commas_between(sub_string) != 2)
		return (free(sub_string), ret_error(E_XYZ_3D_COMMA, current));

// split into three strings
    xyz = ft_split(sub_string, ',');
	if (!xyz)
		return (free(sub_string), ret_error(E_SPLIT, current));
	if (!is_number_valid(xyz[0]) || !is_number_valid(xyz[1]) || !is_number_valid(xyz[2]))
		return (free(sub_string), ret_error(E_XYZ_3D_CHARS, current));
	printf("xyz_3d[0] = %s\n", xyz[0]);
	printf("xyz_3d[1] = %s\n", xyz[1]);
	printf("xyz_3d[2] = %s\n", xyz[2]);
	current->xyz_3d.x = ft_atod(xyz[0], &atoi_overflow);
	current->xyz_3d.y = ft_atod(xyz[1], &atoi_overflow);
	current->xyz_3d.z = ft_atod(xyz[2], &atoi_overflow);
	free_array(xyz);


// check within range
	if (atoi_overflow)
        return (free(sub_string), ret_error(E_XYZ_RANGE, current));
printf("	current->xyz_3d.x = %lf\n", current->xyz_3d.x);
printf("	current->xyz_3d.y = %lf\n", current->xyz_3d.y);
printf("	current->xyz_3d.z = %lf\n", current->xyz_3d.z);
// move pointner past argument
	current->s = current->s + i;

// move pointer to next argument
	current->s = skip_space(current->s);
	// printf("data = %s\n", current->s);
free(sub_string);

return (E_SUCCESS);
}