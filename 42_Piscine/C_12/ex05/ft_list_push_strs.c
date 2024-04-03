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

t_list	*ft_list_push_strs(int size, char **strs)
{
	t_list *begin;
	t_list *element;
	int i;

	begin = NULL;
	i = 0;
	while (i < size && (element = ft_create_elem(strs[i]))) // Verify if all of the element are created.
	{
		element->next = begin;
		begin = element;
		i++;
	}
	return (begin);
}

int main()
{
    char *tab[] = {"element1", "element2", "element3"};
    t_list *list = ft_list_push_strs(3, tab);
    while (list)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return (0);
}