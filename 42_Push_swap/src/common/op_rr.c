/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:18:28 by kaye              #+#    #+#             */
/*   Updated: 2021/03/17 20:27:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	op_rra(t_stack *stacks)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!stacks->a || ft_lstsize(stacks->a) == 1)
		return ;
	tmp = ft_lstlast(stacks->a);
	tmp2 = stacks->a;
	while (tmp2->next->next)
		tmp2 = tmp2->next;
	tmp2->next = NULL;
	ft_lstadd_front(&stacks->a, tmp);
}

void	op_rrb(t_stack *stacks)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!stacks->b || ft_lstsize(stacks->b) == 1)
		return ;
	tmp = ft_lstlast(stacks->b);
	tmp2 = stacks->b;
	while (tmp2->next->next)
		tmp2 = tmp2->next;
	tmp2->next = NULL;
	ft_lstadd_front(&stacks->b, tmp);
}

void	op_rrr(t_stack *stacks)
{
	op_rra(stacks);
	op_rrb(stacks);
}
