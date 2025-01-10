#include "../inc/file_to_list.h"

char    *skip_space(char *s)
{
	if (!s)
		return (NULL);
	while(*s && *s == ' ')
			s++;
	return (s);
}

int	does_file_end_with_rt(char *filename)
{
	int len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	if (ft_strncmp(&filename[len - 3], ".rt", 3))
		return (0);
	return (1);
}
