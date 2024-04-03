/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:01:40 by kaye              #+#    #+#             */
/*   Updated: 2021/03/17 20:27:05 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	op_sa(t_stack *stacks)
{
	void	*tmp;

	if (!stacks->a || ft_lstsize(stacks->a) == 1)
		return ;
	tmp = stacks->a->content;
	stacks->a->content = stacks->a->next->content;
	stacks->a->next->content = tmp;
}

void	op_sb(t_stack *stacks)
{
	void	*tmp;

	if (!stacks->b || ft_lstsize(stacks->b) == 1)
		return ;
	tmp = stacks->b->content;
	stacks->b->content = stacks->b->next->content;
	stacks->b->next->content = tmp;
}

void	op_ss(t_stack *stacks)
{
	op_sa(stacks);
	op_sb(stacks);
}
