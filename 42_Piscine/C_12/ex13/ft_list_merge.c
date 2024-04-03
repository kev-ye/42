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

void ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
    t_list *list;

    list = *begin_list1;
    while (list && list->next)
        list = list->next;
    if (!list)
        *begin_list1 = begin_list2;
    else
        list->next = begin_list2;
}

void ft_list_merge2(t_list **begin_list1, t_list *begin_list2) // Used recursion.
{
    if (!*begin_list1)
        *begin_list1 = begin_list2;
    else if (*begin_list1 && (*begin_list1)->next)
        ft_list_merge2(&(*begin_list1)->next, begin_list2);
    else
        (*begin_list1)->next = begin_list2;
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *element3 = ft_create_elem("element3");
    t_list *element4 = ft_create_elem("element4");
    t_list *element5 = ft_create_elem("element5");
    t_list *element6 = ft_create_elem("element6");
    t_list *list1 = NULL;
    t_list *list2 = NULL;

    list1 = element1;
    if (element1) // Verify if all of the element are created.
        element1->next = element2;
    if (element2)
        element2->next = element3;
    list2 = element4;
    if (element4)
        element4->next = element5;
    if (element5)
        element5->next = element6;
    ft_list_merge(&list1, list2);
    while (list1)
    {
        printf("%s\n", list1->data);
        list1 = list1->next;
    }
    return (0);
}