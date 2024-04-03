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

void ft_sorted_list_insert_element(t_list **list, t_list *element, int (*cmp)()) // function takes in ex16 but have some modification.
{
    if (!*list || cmp(element->data, (*list)->data) <= 0)
    {
        element->next = *list;
        *list = element;
    }
    else
        ft_sorted_list_insert_element(&(*list)->next, element, cmp);
}

void ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2, int (*cmp)())
{
    if (!begin_list2)
        return ;
    ft_sorted_list_merge(begin_list1, begin_list2->next, cmp);
    ft_sorted_list_insert_element(begin_list1, begin_list2, cmp);
}

// i don't found iterative solution for my ft_sorted_list_merge.
// because if i use a loop, the link of begin_list2 change in function of ft_sorted_list_insert_elemen.
// so that giving an infinite loop result.

// another solution.
// you can use function ft_list_merge and ft_list_sort.
// in ft_sorted_list_merge, first use function ft_list_merge to recombine the two lists.
// and use the second function ft_list_sort to sort the list.
// but i think this method isn't very cool so i just write in comments.

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element3");
    t_list *element3 = ft_create_elem("element5");
    t_list *element4 = ft_create_elem("element2");
    t_list *element5 = ft_create_elem("element4");
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
    ft_sorted_list_merge(&list1, list2, &strcmp);
    while (list1)
    {
        printf("%s\n", list1->data);
        list1 = list1->next;
    }
    return (0);
}