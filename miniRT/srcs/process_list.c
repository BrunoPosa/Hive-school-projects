#include "../inc/file_to_list.h"

int	process_list(t_list **l)
{

	// if (list_legality_check(l, LEGAL_CHARS1) == 0)
	// {
	// 	printf("KO - Illegal.\n");
	// 	return(ERROR);
	// }

	if (!list_legality_check(l, LEGAL_CHARS1))
		return (ret_error(E_ILLEGAL_CHARS1, *l));
	move_pointers_to_args(l);
	assign_node_type(l);
	list_legality_check(l, LEGAL_CHARS2); //now there should be only numbers and , etc
	if (process_nodes(l) != E_SUCCESS)
		return (-1);



	// check count of camera, ambiant, light.()

	// take_next_arg_for_type();
	// remove_spaces(l);

	

	return (SUCCESS);
}
void move_pointers_to_args(t_list **l)
{
	t_list *current = *l;

    while (current)
	{
		current->p = skip_space(current->p);
		current = current->next;
	}
}