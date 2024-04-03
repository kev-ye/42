/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:38:57 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 22:34:52 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	clean_all(t_stack *stacks, char *line)
{
	if (line)
		free(line);
	if (stacks)
	{
		if (stacks->split_size)
			ft_lstclear(&stacks->split_size, NULL);
		ft_lstclear(&stacks->a, NULL);
		ft_lstclear(&stacks->b, NULL);
	}
	free(stacks);
	stacks = NULL;
}

void	quit_error(t_stack *stacks, char *line)
{
	clean_all(stacks, line);
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	quit_success(t_stack *stacks, char *msg, char *line)
{
	clean_all(stacks, line);
	if (msg)
		ft_putstr(msg);
	exit(EXIT_SUCCESS);
}
