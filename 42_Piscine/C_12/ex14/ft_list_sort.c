#include <stdlib.h>
#include "ft_list.h"
#include <stdio.h>
#include <string.h>

t_list		*ft_create_elem(void *data)
{
	t_list *list;
	
	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->data = data;
	list->next = NULL;

	return (list);
}

void ft_list_sort(t_list **begin_list, int (*cmp)()) // Ver.1 : change data.
{
    t_list *list;
    void *data;

    list = *begin_list;
    while (list && list->next)
    {
        if (cmp(list->data, list->next->data) > 0)
        {
            data = list->data;
            list->data = list->next->data;
            list->next->data = data;
            list = *begin_list;
        }
        else
            list = list->next;
    }
}

void ft_list_sort2(t_list **begin_list, int (*cmp)()) // Ver.2 : Change link.
{
    t_list *list;
    t_list *prev;

    list = *begin_list;
    prev = NULL;
    while (list && list->next)
    {
        if (cmp(list->data, list->next->data) > 0)
        {
            if (list == *begin_list)
            {
                *begin_list = list->next;
                list->next = list->next->next;
                (*begin_list)->next = list;
            }
            else
            {
                prev->next = list->next;
                list->next = list->next->next;
                prev->next->next = list;
            }
            list = *begin_list;
        }
        else
        {
            prev = list;
            list = list->next;
        }
    }
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element3");
    t_list *element3 = ft_create_elem("element5");
    t_list *element4 = ft_create_elem("element2");
    t_list *element5 = ft_create_elem("element4");
    t_list *element6 = ft_create_elem("element6");
    t_list *list = NULL;

    list = element1;
    if (element1) // Verify if all of the element are created.
        element1->next = element2;
    if (element2)
        element2->next = element3;
    if (element3)
        element3->next = element4;
    if (element4)
        element4->next = element5;
    if (element5)
        element5->next = element6;
    ft_list_sort(&list, &strcmp);
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}