/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundred.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:45:37 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 22:33:40 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	below_median(t_stack *stacks, int i, int size)
{
	while (i < size / 2)
	{
		if ((int)stacks->a->content < stacks->median_a)
		{
			do_op(stacks, "pb");
			++i;
		}
		else
			do_op(stacks, "ra");
	}
	stacks->size_small = ft_lstsize(stacks->b);
}

static void	above_median(t_stack *stacks, int i, int size)
{
	while (i > size / 2)
	{
		if ((int)stacks->a->content >= stacks->median_a)
		{
			do_op(stacks, "pb");
			--i;
		}
	}
	stacks->size_bigger = ft_lstsize(stacks->b);
}

void	action_for_hundred_more(t_stack *stacks)
{
	int	i;
	int	size;

	size = ft_lstsize(stacks->a);
	i = 0;
	below_median(stacks, i, size);
	stack_b_below_median_a(stacks);
	i = size;
	above_median(stacks, i, size);
	stack_b_above_median_a(stacks);
}
