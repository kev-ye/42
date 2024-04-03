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

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *)) // Ver.1.
{
    t_list *prev;
    t_list *list;

    prev = NULL;
    list = *begin_list;
    while (list)
    {
        if (!cmp(list->data, data_ref))
        {
            if (prev)
                prev->next = list->next; // link prev element and next element.
            else
                *begin_list = list->next; // this is for the first element, if we need remove it, we just need to move on the next element.
            if (free_fct)
                free_fct(list->data);
            free(list);
            list = ((prev) ? prev->next : *begin_list); // is same if we use "list = list->next", because in the memory, we have linked prev element and next element.
        }
        else
        {
            prev = list; // save the prev element.
            list = list->next;
        }
    }
}

void ft_list_remove_if2(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *)) // Ver.2.
{
    t_list *current;
    t_list *remove;

    current = *begin_list;
    while (current && current->next)
    {
        if (!cmp(current->next->data, data_ref))
        {
            remove = current->next;
            current->next = current->next->next; // replace the next element with next next element.
            if (free_fct)
                free_fct(remove->data);
            free(remove);
        }
        current = current->next;
    }
    current = *begin_list;
    if (current && !cmp(current->data, data_ref)) // for the first element, if we need remove it.
    {
        *begin_list = current->next;
        if (free_fct)
            free_fct(current->data);
        free(current);
    }
}

void ft_list_remove_if3(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *)) // Used recursion.
{
    t_list *remove;

    if (!*begin_list)
        return ;
    if (!cmp((*begin_list)->data, data_ref))
    {
        remove = *begin_list;
        *begin_list = (*begin_list)->next;
        if (free_fct)
            free_fct(remove->data);
        free(remove);
        ft_list_remove_if3(begin_list, data_ref, cmp, free_fct); // parameter : begin_list == &(*begin_list).
    }
    else
        ft_list_remove_if3(&(*begin_list)->next, data_ref, cmp, free_fct);
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
    ft_list_remove_if(&list, "element1", &strcmp, NULL);
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}