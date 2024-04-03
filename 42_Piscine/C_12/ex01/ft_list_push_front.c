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

void ft_list_push_front(t_list **begin_list, void *data)
{
    t_list *element;

    if ((element = ft_create_elem(data))) // Verify if all of the element are created.
    {
        if (*begin_list)
            element->next = *begin_list;
        *begin_list = element;
    }
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *list;
    
    list = element1;
    if (element1) // Verify if all of the element are created.
        element1->next = element2;
    ft_list_push_front(&list, "insert element");
    while (list)
    {
	    printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}

