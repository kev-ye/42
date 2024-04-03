/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:10:50 by kaye              #+#    #+#             */
/*   Updated: 2021/03/09 19:37:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	const char	*str;

	if (!s)
		return (0);
	str = s;
	while (*str)
		++str;
	return (str - s);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		*str++ = s1[i++];
	i = 0;
	while (s2 && s2[i])
		*str++ = s2[i++];
	*str = '\0';
	free((char *)s1);
	return (str - len);
}

t_set	*ft_lstnew_gnl(void)
{
	t_set	*new;

	new = (t_set *)malloc(sizeof(t_set));
	if (new)
	{
		new->fd = 0;
		new->str = NULL;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_front_gnl(t_set **alst, t_set *new)
{
	if (*alst)
		new->next = *alst;
	*alst = new;
}

void	ft_list_remove_gnl(t_set **alst)
{
	t_set	*prev;
	t_set	*list;

	prev = NULL;
	list = *alst;
	while (list)
	{
		if (!list->str)
		{
			if (prev)
				prev->next = list->next;
			else
				*alst = list->next;
			free(list);
			if (prev)
				list = prev->next;
			else
				list = *alst;
		}
		else
		{
			prev = list;
			list = list->next;
		}
	}
}
