#include "../inc/file_to_list.h"
#include "../../libft/libft.h"

int	main(int argc, char **argv)
{
	(void)argv;
	printf("Test\n\n");
	if (argc != 2)
	{
		printf("Error: no file given\n");
		return (1);
	}


// t_list *l;
// file_to_list(argv[1], &l);
// assign_scene_object(l);
// // checkif there are two camera, if camera >1 retuirn error

// ft_list_print(l);





	// ft_list_print(ft_file_to_list(argv[1]));
	return (0);
}

// int	file_to_list(char *argv, t_list *l)
// {
// 	int fd;
// 	char *line;
// 	int ret;

// 	fd = open(argv, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error: file not found\n");
// 		return (-1);
// 	}
// 	while ((ret = get_next_line(fd, &line)) > 0)
// 	{
// 		ft_list_push_back(l, line);
// 	}
// 	if (ret == -1)
// 	{
// 		printf("Error: file not found\n");
// 		return (-1);
// 	}
// 	close(fd);
// 	return (0);
// }