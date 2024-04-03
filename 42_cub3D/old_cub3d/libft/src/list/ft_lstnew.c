/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:57:23 by kaye              #+#    #+#             */
/*   Updated: 2020/11/04 17:41:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and returns a new element.
** Returns NULL on error.
*/

t_list		*ft_lstnew(void *content)
{
	t_list *new;

	if ((new = (t_list *)malloc(sizeof(t_list))))
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}
