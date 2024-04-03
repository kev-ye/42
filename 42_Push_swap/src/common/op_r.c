/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:18:24 by kaye              #+#    #+#             */
/*   Updated: 2021/03/17 20:27:10 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	op_ra(t_stack *stacks)
{
	t_list	*tmp;

	if (!stacks->a || ft_lstsize(stacks->a) == 1)
		return ;
	tmp = stacks->a;
	stacks->a = stacks->a->next;
	tmp->next = NULL;
	ft_lstadd_back(&stacks->a, tmp);
}

void	op_rb(t_stack *stacks)
{
	t_list	*tmp;

	if (!stacks->b || ft_lstsize(stacks->b) == 1)
		return ;
	tmp = stacks->b;
	stacks->b = stacks->b->next;
	tmp->next = NULL;
	ft_lstadd_back(&stacks->b, tmp);
}

void	op_rr(t_stack *stacks)
{
	op_ra(stacks);
	op_rb(stacks);
}
