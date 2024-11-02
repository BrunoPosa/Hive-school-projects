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
	check_count_of_types(l);


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