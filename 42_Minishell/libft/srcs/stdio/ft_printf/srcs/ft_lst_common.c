/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 21:57:23 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:52:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

t_data	*ft_lstd_new(char *data, int size)
{
	t_data	*new;

	if (!data)
		return (NULL);
	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->data = ft_strdup(data);
	new->size = size;
	new->next = NULL;
	return (new);
}

t_data	*ft_lstd_last(t_data *lst)
{
	t_data	*last;

	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_lstd_add(t_data **lst, t_data *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstd_last(*lst)->next = new;
	else
		*lst = new;
}

void	ft_lstd_print(t_data **s, int *size, int fd)
{
	t_data	**tracer;

	tracer = s;
	while (*tracer)
	{
		write(fd, (*tracer)->data, (*tracer)->size);
		*size += (*tracer)->size;
		tracer = &(*tracer)->next;
	}
}

void	ft_lstd_clear(t_data **lst)
{
	t_data	*tmp;

	while (*lst)
	{
		if ((*lst)->data)
			free((*lst)->data);
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
