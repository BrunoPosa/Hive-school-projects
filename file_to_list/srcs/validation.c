#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

int	only_legal_chars(char *s)
{
	int	i;

	i = -1;
	while(s[++i])
	{
		if (ft_strchr(LEGAL_CHARS1, s[i]) == NULL)
		{
			// printf("i=%d\n", i);
			return (0);
		}
	}
	return (1);
}

int is_file_legal(char *filename)
{
    int fd;
    char *line;

    if(!does_filename_end_with_rt(filename))
        return (-1);//E_FILE_NAME
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (-1);//E_FILE_NAME
    line = get_next_line(fd);
    while (line)
    {
        if (!legal_line(line))
        {
            free(line);
            close(fd);
            return (-1);//E_ARGS
        }
        line = get_next_line(fd);
        free(line);
    }
    close(fd);
    return (0);//NO_ERROR
}
