/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:21:47 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 13:40:22 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstprint(t_list *lst, char sep)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
			ft_printf("%s%c", tmp->content, sep);
		tmp = tmp->next;
	}
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*list;
	void	*content;

	list = *begin_list;
	while (list && list->next)
	{
		if (cmp(list->content, list->next->content) > 0)
		{
			content = list->content;
			list->content = list->next->content;
			list->next->content = content;
			list = *begin_list;
		}
		else
			list = list->next;
	}
}

char	**ft_lst2strs(t_list **lst)
{
	size_t	tmp_len;
	char	**new;
	t_list	*tmp;
	size_t	i;

	if (!lst || !*lst)
		return (NULL);
	new = ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	tmp = *lst;
	while (tmp)
	{
		tmp_len = ft_strlen(tmp->content);
		new[i] = (char *)ft_calloc(tmp_len + 1, sizeof(char));
		if (!new[i])
			return (ft_strsfree(i, new));
		ft_memcpy(new[i++], tmp->content, tmp_len);
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}
