#include "../inc/file_to_list.h"


int	file_to_list(char *filename, t_list **l)
{
	int fd;
	char *line;
	t_list *tmp;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			printf("Error: malloc failed\n");
			return (-1);
		}
		ft_lstadd_back(l, tmp);
		line = get_next_line(fd);	
	}
	close(fd);
	return (0);
}