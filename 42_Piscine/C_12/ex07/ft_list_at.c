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

t_list *ft_list_at(t_list *begin_list, unsigned int nbr)
{
    unsigned int i;

    i = 0;
    while (i < nbr)
    {
        if (!begin_list)
            return (NULL);
        begin_list = begin_list->next;
        i++;
    }
    return (begin_list);
}

t_list *ft_list_at2(t_list *begin_list, unsigned int nbr) // Used recursion Ver.1.
{
    if (!begin_list)
        return (NULL);
    return ((nbr) ? ft_list_at2(begin_list->next, nbr - 1) : begin_list);
}

t_list	*ft_list_at3(t_list *begin_list, unsigned int nbr) // Used recursion Ver.2.
{
	if (!begin_list || !nbr)
		return (begin_list);
	return (ft_list_at3(begin_list->next, nbr - 1));
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *element3 = ft_create_elem("element3");
    t_list *list = NULL;
    t_list *at;

    list = element1;
    if (element1) // Verify if all of the element are created
        element1->next = element2;
    if (element2)
        element2->next = element3;
    at = ft_list_at(list, 0);
    printf("%s\n", at->data);
    return (0);
}