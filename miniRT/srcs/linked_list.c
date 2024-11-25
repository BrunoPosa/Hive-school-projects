#include "../inc/file_to_list.h"

t_list *ft_lstnew(void *s)
{
	t_list *new_node;

	new_node = (t_list *)ft_calloc(1, sizeof(t_list));

	if (!new_node)
		return (NULL);
	new_node->s = s;
	new_node->next = NULL;
	return (new_node);
}
t_list *ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		(ft_lstlast(*lst))->next = new;
}



// t_list *c(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_list;
// 	t_list	*new_node;
// 	void	*tmp;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	new_list = NULL;
// 	while (lst)
// 	{
// 		tmp = f(lst->s);
// 		new_node = ft_lstnew(tmp);
// 		if (!(new_node))
// 		{
// 			ft_lstclear(&new_list, del);
// 			if (tmp)
// 				free(tmp);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&new_list, new_node);
// 		lst = lst->next;
// 	}
// 	return (new_list);
// }

// add a new node with no next node



// tell us the size of a list
int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return ((int)i);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:27:27 by jtu               #+#    #+#             */
/*   Updated: 2023/11/10 17:05:27 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * Deletes and frees the given node and every
 * successor of that node, using the function ’del’
 * and free(3).
 * Finally, the pointer to the list must be set to
 * NULL.
 * @param lst - The address of a pointer to a node.
 * @param del - The address of the function used to
 *              delete the content of the node.
 * @return None
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !(*lst))
		return ;
	ft_lstclear(&((*lst)->next), del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:53:41 by jtu               #+#    #+#             */
/*   Updated: 2023/11/14 18:17:03 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Takes as a parameter a node and frees the memory of
 * the node’s content using the function ’del’ given
 * as a parameter and free the node. The memory of
 * ’next’ must not be freed.
 * @param lst - The node to free.
 * @param del - The address of the function used to delete
 * the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->s);
	free(lst);
}