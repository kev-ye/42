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

void ft_list_foreach_if(t_list *begin_list, void (*f)(void *), void *data_ref, int (*cmp)())
{
    while (begin_list)
    {
        if (!cmp(begin_list->data, data_ref))
            f(begin_list->data);
        begin_list = begin_list->next;
    }
}

void ft_list_foreach_if2(t_list *begin_list, void (*f)(void *), void *data_ref, int (*cmp)()) // Used recursion.
{
    if (!begin_list)
        return ;
    if (!cmp(begin_list->data, data_ref))
            f(begin_list->data);
    ft_list_foreach_if2(begin_list->next, f, data_ref, cmp); 
}

void    f(void *data) // function for print data.
{
    printf("%s\n", data);
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
    ft_list_foreach_if(list, &f, "element1", &strcmp);
    return (0);
}