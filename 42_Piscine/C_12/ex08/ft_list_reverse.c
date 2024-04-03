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

void ft_list_reverse(t_list **begin_list)
{
    t_list *prev;
    t_list *next;

    prev = NULL;
    while (*begin_list)
    {
        next = (*begin_list)->next;
        (*begin_list)->next = prev;
        prev = *begin_list;
        *begin_list = next;
    }
    *begin_list = prev;
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *element3 = ft_create_elem("element3");
    t_list *list = NULL;
    t_list *tmp;

    list = element1;
    if (element1) // Verify if all of the element are created.
        element1->next = element2;
    if (element2)
        element2->next = element3;
    tmp = list; // save initial address of list for After.
    printf("////// Before //////\n");
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    list = tmp; // back to initial address of list.
    ft_list_reverse(&list);
    printf("////// After //////\n");
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}