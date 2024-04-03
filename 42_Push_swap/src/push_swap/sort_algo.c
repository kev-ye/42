/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:14:05 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 20:18:27 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_stack_b_to_a(t_stack *stacks)
{
	int	first_a;

	first_a = (int)stacks->a->content;
	while (stacks->b)
	{
		stacks->bigger = get_bigger(stacks->b);
		stacks->smaller = get_smaller(stacks->b);
		if ((int)stacks->b->content == stacks->smaller)
		{
			do_op(stacks, "pa");
			do_op(stacks, "ra");
		}
		else if ((int)stacks->b->content == stacks->bigger)
			do_op(stacks, "pa");
		else if ((int)ft_lstlast(stacks->b)->content == stacks->smaller
			|| (int)ft_lstlast(stacks->b)->content == stacks->bigger)
			do_op(stacks, "rrb");
		else if ((int)stacks->b->content > stacks->smaller
			&& (int)stacks->b->content < stacks->bigger)
			do_op(stacks, "rb");
	}
	while ((int)stacks->a->content != first_a)
		do_op(stacks, "ra");
}

static void	median_split_b(t_stack *stacks)
{
	int	count;
	int	size;
	int	i;

	while (stacks->b)
	{
		count = 0;
		stacks->median_b = get_median(stacks->b, stacks,
				ft_lstsize(stacks->b));
		size = ft_lstsize(stacks->b);
		i = size;
		while (i > size / 2)
		{
			if ((int)stacks->b->content >= stacks->median_b)
			{
				do_op(stacks, "pa");
				--i;
				++count;
			}
			else
				do_op(stacks, "rb");
		}
		ft_lstadd_front(&stacks->split_size,
			ft_lstnew((void *)(intptr_t)count));
	}
}

static void	split_and_sort(
	t_stack *stacks,
	int r_a,
	int median,
	t_list *split_size)
{
	int	i;

	i = 0;
	r_a = 0;
	median = get_median(stacks->a, stacks, (int)split_size->content);
	while (i < (int)split_size->content)
	{
		if ((int)stacks->a->content >= median)
		{
			do_op(stacks, "ra");
			++r_a;
		}
		else
			do_op(stacks, "pb");
		++i;
	}
	i = -1;
	while (++i < r_a)
		do_op(stacks, "rra");
	sort_stack_b_to_a(stacks);
	while (i--)
		do_op(stacks, "pb");
	sort_stack_b_to_a(stacks);
}

void	stack_b_below_median_a(t_stack *stacks)
{
	int		r_a;
	int		median;
	t_list	*tmp;

	stacks->split_size = NULL;
	median_split_b(stacks);
	tmp = stacks->split_size;
	while (tmp)
	{
		if ((int)tmp->content == 1)
			do_op(stacks, "ra");
		else if ((int)tmp->content == 2)
		{
			if ((int)stacks->a->content > (int)stacks->a->next->content)
				do_op(stacks, "sa");
			do_op(stacks, "ra");
			do_op(stacks, "ra");
		}
		else
			split_and_sort(stacks, r_a, median, tmp);
		tmp = tmp->next;
	}
	ft_lstclear(&stacks->split_size, NULL);
}

void	stack_b_above_median_a(t_stack *stacks)
{
	int		r_a;
	int		median;
	t_list	*tmp;

	stacks->split_size = NULL;
	median_split_b(stacks);
	tmp = stacks->split_size;
	while (tmp)
	{
		if ((int)tmp->content == 1)
			do_op(stacks, "ra");
		else if ((int)tmp->content == 2)
		{
			if ((int)stacks->a->content > (int)stacks->a->next->content)
				do_op(stacks, "sa");
			do_op(stacks, "ra");
			do_op(stacks, "ra");
		}
		else
			split_and_sort(stacks, r_a, median, tmp);
		tmp = tmp->next;
	}
}
