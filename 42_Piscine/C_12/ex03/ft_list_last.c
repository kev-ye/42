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

t_list *ft_list_last(t_list *begin_list)
{
    t_list *save;

    while (begin_list)
    {
        save = begin_list;
        begin_list = begin_list->next;
    }
    return (save);
}

t_list *ft_list_last2(t_list *begin_list) //Used recursion.
{
    return ((!begin_list) ? ft_list_last2(begin_list->next) : begin_list);
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *element3 = ft_create_elem("element3");
    t_list *list;

    list = element1;
    if (element1) // Verify if all of the element are created.
        element1->next = element2;
    if (element2)
        element2->next = element3;
    t_list *last = ft_list_last(list);
    t_list *last2 = ft_list_last(list);
    printf("No recursion : %s\n", last->data);
    printf("Recursion : %s\n", last2->data);
    return (0);
}