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

void ft_list_reverse_fun(t_list *begin_list) // Ver.1 : 1 by 1 => swap data of list with data of tmp_list.
{
    t_list *tmp_list;
    void *data;

    while (begin_list)
    {
        tmp_list = begin_list; // initialize tmp_list.
        while (tmp_list && tmp_list->next)
        {
            data = begin_list->data; // save data of begin_list.
            begin_list->data = tmp_list->next->data; // swap data of begin_list with data of tmp_list.
            tmp_list->next->data = data; // replace data of begin_list in tmp_list.
            tmp_list = tmp_list->next; // go in to next of tmp_list.
        }
        begin_list = begin_list->next; // go in to next of begin_list.
    }
}

static int	ft_list_size(t_list *begin_list) // function for ft_list_reverse_fun2 and ft_list_reverse_fun3.
{
	return ((begin_list) ? 1 + ft_list_size(begin_list->next) : 0);
}

static t_list *ft_list_at(t_list *begin_list, unsigned int nbr) // function for ft_list_reverse_fun2 and ft_list_reverse_fun3.
{
    if (!begin_list)
        return (NULL);
    return ((nbr) ? ft_list_at(begin_list->next, nbr - 1) : begin_list);
}

void ft_list_reverse_fun2(t_list *begin_list) // Ver.2 : list / 2 => swap data of left list with data of right list.
{
	void *data;
    int	left;
	int	right;

	left = 0;
    right = ft_list_size(begin_list) - 1;
	while (left < (ft_list_size(begin_list) / 2))
	{
        data = ft_list_at(begin_list, left)->data; // save data of left list.
        ft_list_at(begin_list, left)->data = ft_list_at(begin_list, right)->data; // swap data of left list with data of right list.
        ft_list_at(begin_list, right)->data = data; // swap data of right list with data of left list.
        left++; // go in to next of left list.
        right--; // go in to next of right list.
	} 
}

void ft_list_reverse_fun3(t_list *begin_list) // Ver.3 : list / 2 => swap data of left list with data of right list.
{
    t_list *right_list;
    void *data;
    int i;
    int right;

    i = 0;
    while (begin_list && (right = ft_list_size(begin_list) - i) > 1)
    {
        right_list = ft_list_at(begin_list, right - 1); // initialise right_list.
        data = begin_list->data; // save data of begin_list.
        begin_list->data = right_list->data; // swap data of begin_list with data of right_list.
        right_list->data = data; // swap data of right_list with data of begin_list.
        begin_list = begin_list->next;
        i++; 
    }
}

int main()
{
    t_list *element1 = ft_create_elem("element1");
    t_list *element2 = ft_create_elem("element2");
    t_list *element3 = ft_create_elem("element3");
    t_list *element4 = ft_create_elem("element4");
    t_list *element5 = ft_create_elem("element5");
    t_list *element6 = ft_create_elem("element6");
    t_list *list = NULL;
    t_list *tmp;

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
    tmp = list; // save initial address of list for After.
    printf("////// Before //////\n");
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    list = tmp; // reinitialize address of list.
    ft_list_reverse_fun(list);
    printf("////// After //////\n");
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}