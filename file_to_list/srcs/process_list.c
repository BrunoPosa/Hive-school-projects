#include "../inc/file_to_list.h"

int	process_list(t_list **l)
{

	// if (list_legality_check(l, LEGAL_CHARS1) == 0)
	// {
	// 	printf("KO - Illegal.\n");
	// 	return(ERROR);
	// }

	list_legality_check(l, LEGAL_CHARS1); //only certain letters and numbers should be here
	move_pointer_to_arg(l);
	assign_node_type(l);
	list_legality_check(l, LEGAL_CHARS2); //now there should be only numbers and , etc
	process_nodes(l);


	// check count of camera, ambiant, light.()

	// take_next_arg_for_type();
	// remove_spaces(l);

	

	return (SUCCESS);
}
void move_pointer_to_arg(t_list **l)
{
	t_list *current = *l;

    while (current)
	{
		current->s = skip_space(current->s);
		current = current->next;
	}
}
int	only_legal_chars(char *s, char *legal)
{
	int	i;

	i = -1;
	while(s[++i])
	{
		if (ft_strchr(legal, s[i]) == NULL)
		{
			// printf("i=%d\n", i);
			return (0);
		}
	}
	return (1);
}

int	list_legality_check(t_list **l, char *legal)
{

    t_list *current = *l;

    while (current)
	{	
			
		if(!only_legal_chars(current->s, legal))
		{
			printf("KO - illegal char!\n");
			return 0;
		}
		current = current->next;
	}
	printf("OK - File has only legal chars.\n");
	return 1;
}

