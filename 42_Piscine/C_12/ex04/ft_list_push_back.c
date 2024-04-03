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

void	ft_list_push_back(t_list **begin_list, void *data)
{
    t_list *tmp;

    tmp = *begin_list;
    if (tmp == NULL)
        *begin_list = ft_create_elem(data);
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = ft_create_elem(data);
    }
}

void	ft_list_push_back2(t_list **begin_list, void *data) // Used recursion Ver.1.
{
    t_list *tmp;

    tmp = *begin_list;
    if (tmp == NULL)
        *begin_list = ft_create_elem(data);
    else if (tmp->next)
        ft_list_push_back2(&tmp->next, data);
    else
        tmp->next = ft_create_elem(data);
}

void	ft_list_push_back3(t_list **begin_list, void *data) // Used recursion Ver.2.
{
	if (!*begin_list)
		*begin_list = ft_create_elem(data);
	else if ((*begin_list)->next)
		ft_list_push_back2(&(*begin_list)->next, data);
	else
		(*begin_list)->next = ft_create_elem(data);
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
    ft_list_push_back(&list, "insert element");
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}