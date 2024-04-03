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

void ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)())
{
    t_list *list;
    t_list *element;

    list = *begin_list;
    if(!(element = ft_create_elem(data)))
        return ;
    if (!list)
    {
        list = element;
        return ;
    }
    if (cmp(data, list->data) < 0) // for first element of list.
    {
        element->next = *begin_list;
        *begin_list = element;
        return ;
    }
    while (list->next && cmp(data, list->next->data) >= 0) // search element if resultat of cmp has greater than of equal to zero.
        list = list->next;
    element->next = list->next;
    list->next = element;
}

void ft_sorted_list_insert2(t_list **begin_list, void *data, int (*cmp)()) // used recursion.
{
    t_list *element;

    if (!*begin_list || cmp(data, (*begin_list)->data) <= 0) // if begin_list equal NULL or result of cmp has less than or equal to zero that insert element.
    {
        if (!(element = ft_create_elem(data)))
            return ;
        element->next = *begin_list;
        *begin_list = element;
    }
    else
        ft_sorted_list_insert2(&(*begin_list)->next, data, cmp);
}

// another solution.
// you can use function ft_list_push_front and ft_list_sort.
// in ft_sorted_list_insert, first use function ft_list_push_front to add the element in list.
// and use the second function ft_list_sort to sort the list.
// but i think this method isn't very cool so i just write in comments.

int main()
{
    t_list *element1 = ft_create_elem("element2");
    t_list *element2 = ft_create_elem("element3");
    t_list *element3 = ft_create_elem("element4");
    t_list *element4 = ft_create_elem("element5");
    t_list *element5 = ft_create_elem("element6");
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
    ft_sorted_list_insert(&list, "element1", &strcmp);
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}