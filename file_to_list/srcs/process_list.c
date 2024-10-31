#include "../inc/file_to_list.h"
void test_pos(t_list **l);

int	process_list(t_list **l)
{
	if (list_legality_check(l) == 0)
	{
		printf("KO - Illegal.\n");
		return(ERROR);
	}
	// move_pointer_to_arg(l);
	assign_node_type(l);
	// 		if first chars == pl -> this is enum 3
	// 		if first chars = sp -> this is enum 4
	move_pointer_to_arg();
	check_chars_second_time();
		if we have a lp, that wouldn't haave been passed so it fails the check
	
	// check count of camera, ambiant, light.()

	take_next_arg_for_type();
	// remove_spaces(l);

	test_pos(l);

	return (SUCCESS);
}
void move_pointer_to_arg(t_list **l)
{
	t_list *current = *l;

    while (current)
	{
		current->content = skip_space(current->content);
		current = current->next;
	}
}


int	list_legality_check(t_list **l)
{
    t_list *current = *l;

    while (current)
	{	
		if(!only_legal_chars(current->content))
		{
			printf("KO - illegal char!\n");
			return 0;
		}
		current = current->next;
	}
	printf("OK - File has only legal chars.\n");
	return 1;
}

int	only_legal_chars(char *s)
{
	int	i;

	i = -1;
	while(s[++i])
	{
		if (ft_strchr(LEGAL_CHARS, s[i]) == NULL)
		{
			// printf("i=%d\n", i);
			return (0);
		}
	}
	return (1);
}

void test_pos(t_list **l)
{
    t_list *current = *l;

    while (current) {
        current->pos = ft_strlen(current->content2);

        current = current->next;
    }
}

void remove_spaces(t_list **l)
{
    t_list *current = *l;

    while (current) {
        current->content2 = "test\n";
        current->content2 = process(current->content);
		current->content3 = process2(current->content2);

        current = current->next;
    }
}

