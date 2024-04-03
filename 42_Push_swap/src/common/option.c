/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:38:13 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 20:11:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	show_stack_v(t_list *a, t_list *b)
{
	if (a == NULL && b == NULL)
		return ;
	if (a && b)
		ft_printf("| %12d | %-12d |\n", (int)a->content, (int)b->content);
	else if (a)
		ft_printf("| %12d | %-12c |\n", (int)a->content, ' ');
	else if (b)
		ft_printf("| %12c | %-12d |\n", ' ', (int)b->content);
	if (a && b)
		show_stack_v(a->next, b->next);
	else if (a)
		show_stack_v(a->next, NULL);
	else if (b)
		show_stack_v(NULL, b->next);
}

static void	option_v(t_stack *stacks)
{
	if (stacks->flag_v != 1)
		return ;
	usleep(50000);
	ft_putstr("\033[2J\033[H");
	ft_printf("-------------------------------\n");
	ft_printf("| %12s | %-12s |\n", "Stack A", "Stack B");
	ft_printf("-------------------------------\n");
	show_stack_v(stacks->a, stacks->b);
	ft_printf("-------------------------------\n");
}

static void	show_stack_b(t_stack *stacks, t_list *a, t_list *b)
{
	int	b_a;
	int	b_b;

	if (a == NULL && b == NULL)
		return ;
	if (a)
		b_a = ((double)(int)a->content / stacks->max) * 50;
	if (b)
		b_b = ((double)(int)b->content / stacks->max) * 50;
	if (a)
		ft_printf(F_CYAN"%*.0d"NONE"%*.0d", b_a, 0, 50 - b_a, 0);
	else
		ft_printf("%*.0d", 50, 0);
	if (b)
		ft_printf(F_YELLOW"%*.0d"NONE"%*.0d\n", b_b, 0, 50 - b_b, 0);
	else
		ft_printf("%*.0d\n", 50, 0);
	if (a && b)
		show_stack_b(stacks, a->next, b->next);
	else if (a)
		show_stack_b(stacks, a->next, NULL);
	else if (b)
		show_stack_b(stacks, NULL, b->next);
}

static void	option_b(t_stack *stacks)
{
	int	max;

	if (stacks->flag_b != 1)
		return ;
	usleep(50000);
	ft_putstr("\033[2J\033[H");
	show_stack_b(stacks, stacks->a, stacks->b);
}

void	show_stacks_option(t_stack *stacks)
{
	if (stacks->flag_v && stacks->flag_b)
	{
		usleep(100000);
		ft_putstr("\033[2J\033[H");
		ft_printf(RED"OPTION V : \n\n"NONE);
		ft_printf("-------------------------------\n");
		ft_printf("| %12s | %-12s |\n", "Stack A", "Stack B");
		ft_printf("-------------------------------\n");
		show_stack_v(stacks->a, stacks->b);
		ft_printf("-------------------------------\n");
		ft_printf(RED"\nOPTION B : \n\n"NONE);
		show_stack_b(stacks, stacks->a, stacks->b);
	}
	else if (stacks->flag_v)
		option_v(stacks);
	else if (stacks->flag_b)
		option_b(stacks);
}
