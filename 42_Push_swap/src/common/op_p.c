/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:18:21 by kaye              #+#    #+#             */
/*   Updated: 2021/03/17 20:27:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	op_pa(t_stack *stacks)
{
	t_list	*tmp;

	if (!stacks->b)
		return ;
	tmp = stacks->b->next;
	stacks->b->next = NULL;
	ft_lstadd_front(&stacks->a, stacks->b);
	stacks->b = tmp;
}

void	op_pb(t_stack *stacks)
{
	t_list	*tmp;

	if (!stacks->a)
		return ;
	tmp = stacks->a->next;
	stacks->a->next = NULL;
	ft_lstadd_front(&stacks->b, stacks->a);
	stacks->a = tmp;
}
