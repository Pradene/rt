#include "../../includes/parsing.h"

static t_obj_list   *last_objects(t_obj_list *lst)
{
    t_obj_list  *tmp;

    if (!lst)
        return (NULL);
    tmp = lst;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

void    free_objects(t_obj_list **lst)
{
    t_obj_list  *tmp;

    if (!lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        free(*lst);
        (*lst) = tmp;
    }
}

void    add_objects(t_obj_list **lst, t_obj_list *new)
{
    t_obj_list	*tmp;

	if (!lst)
        return ;
	if (*lst)
	{
		tmp = last_objects(*lst);
		tmp->next = new;
	}
	else
    {
		*lst = new;
    }
}
