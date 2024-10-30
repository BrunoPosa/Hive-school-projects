#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

int	main(int argc, char **argv)
{
	t_list *l = NULL;

	if (argc != 2)
	{
		printf("Error: no file given\n");
		return (1);
	}
	file_to_list(argv[1], &l);
// assign_scene_object(l);
// // checkif there are two camera, if camera >1 retuirn erroro

	ft_list_print(&l);

	return (0);
}

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
		ft_lstadd_back(l, tmp);
		line = get_next_line(fd);	
	}

	close(fd);
	return (0);
}