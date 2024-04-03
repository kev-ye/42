/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:43:35 by kaye              #+#    #+#             */
/*   Updated: 2021/12/12 20:59:13 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static void	_print_value(char *key)
{
	t_map	*mapped;

	if (!key || key[0] == '\0')
		return ;
	mapped = get_map(key);
	if (NULL != mapped)
	{
		ft_putstr_fd(mapped->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(key, STDOUT_FILENO);
		ft_putstr_fd(": Not found.\n", STDOUT_FILENO);
	}
}

void	run(void)
{
	t_hr		*ptr;
	uint64_t	i;

	ptr = sgt();
	i = ptr->save_index;
	while (i < ptr->len)
	{
		_print_value(ptr->buff + i);
		i += ft_strlen(ptr->buff + i) + 1;
	}
}
