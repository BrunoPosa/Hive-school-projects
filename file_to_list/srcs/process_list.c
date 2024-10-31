#include "../inc/file_to_list.h"

void	process_list(t_list **l)
{
	remove_spaces(l);
}

void remove_spaces(t_list **l)
{
    t_list *current = *l;

    while (current) {
        // current->content2 = "test\n";
        current->content2 = process(current->content);
		current->content3 = process2(current->content2);

        current = current->next;
    }
}

