/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:53:12 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 20:11:10 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_op(t_stack *stacks, char *op_name)
{
	const t_op	op[OP_AMOUT] = {
		{"sa", op_sa}, {"sb", op_sb}, {"ss", op_ss}, {"pa", op_pa},
		{"pb", op_pb}, {"ra", op_ra}, {"rb", op_rb}, {"rr", op_rr},
		{"rra", op_rra}, {"rrb", op_rrb}, {"rrr", op_rrr}
	};
	int			i;

	i = -1;
	while (++i < OP_AMOUT)
	{
		if (!ft_strcmp(op_name, op[i].name))
		{
			op[i].f(stacks);
			if (!stacks->flag_v)
			{
				ft_putstr(op_name);
				ft_putchar('\n');
			}
			show_stacks_option(stacks);
			return ;
		}
	}
}
