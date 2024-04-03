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

t_list *ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
    while (begin_list)
    {
        if (!cmp(begin_list->data, data_ref))
            return(begin_list);
        begin_list = begin_list->next;
    }
    return (begin_list);
}

t_list *ft_list_find2(t_list *begin_list, void *data_ref, int (*cmp)()) // Used recursion.
{
    if (!begin_list || !cmp(begin_list->data, data_ref))
        return (begin_list);
    return(ft_list_find2(begin_list->next, data_ref, cmp));
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *element3 = ft_create_elem("element3");
    t_list *list = NULL;
    t_list *find;

    list = element1;
    if (element1) // Verify if all of the element are created.
        element1->next = element2;
    if (element2)
        element2->next = element3;
    find = ft_list_find2(list, "element1", &strcmp);
    while (find)
    {
        printf("%s\n", find->data);
        find = find->next;
    }
    return (0);
}