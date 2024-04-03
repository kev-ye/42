/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:29:32 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 22:16:41 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**lst2tab(t_list *to_tab)
{
	char	**ret;
	size_t	size;
	int		i;

	size = ft_lstsize(to_tab);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (NULL == ret)
		exit_clean(E_SYS, __FILE__, __LINE__);
	i = 0;
	while (NULL != to_tab)
	{
		ret[i++] = (char *)to_tab->content;
		to_tab = to_tab->next;
	}
	ret[i] = NULL;
	return (ret);
}

size_t	strslen(char **sstr)
{
	size_t	i;

	i = 0;
	while (NULL != sstr[i])
		++i;
	return (i);
}

int	gnl(int const *fd, char **line,	void *to_free)
{
	int	ret;

	ret = get_next_line(*fd, line);
	if (ret < 0)
	{
		if (NULL != to_free)
			free_clean((void **)&to_free);
		close(*fd);
		exit_clean(E_SYS, __FILE__, __LINE__);
	}
	return (ret);
}

void	free_clean(void **to_free)
{
	if (NULL != to_free && NULL != *to_free)
		free(*to_free);
	*to_free = NULL;
}
