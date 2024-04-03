#include <stdlib.h>
#include "ft_list.h"
#include <stdio.h>

t_list		*ft_create_elem(void *data)
{
	t_list *list;
	
	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->data = data;
	list->next = NULL;

	return (list);
}

void    ft_list_clear(t_list *begin_list, void (*free_fct)(void *))
{
    t_list	*tmp;

    tmp = NULL;
    while (begin_list)
    {
        if (free_fct)
            free_fct(begin_list->data);
        tmp = begin_list;
        begin_list = begin_list->next;
        free(tmp);
    }
}

void    ft_list_clear2(t_list *begin_list, void (*free_fct)(void *)) // Used recursion Ver.1.
{
    t_list *tmp;

    if (!begin_list)
        return ;
    if (free_fct)
        free_fct(begin_list->data);
    tmp = begin_list;
    free(tmp);
    ft_list_clear2(begin_list->next, free_fct);
}

void    ft_list_clear3(t_list *begin_list, void (*free_fct)(void *)) // Used recursion Ver.2.
{
    if (!begin_list)
        return ;
    ft_list_clear3(begin_list->next, free_fct);
    if (free_fct)
        free_fct(begin_list->data);
    free(begin_list);
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *element3 = ft_create_elem("element3");
    t_list *list = NULL;

    list = element1;
    if (element1) // Verify if all of the element are created.
        element1->next = element2;
    if (element2)
        element2->next = element3;
    ft_list_clear(list, NULL);
    return (0);
}