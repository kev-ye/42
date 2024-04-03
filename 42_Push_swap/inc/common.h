#ifndef COMMON_H
# define COMMON_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "libft.h"
# define OP_AMOUT 11

typedef struct s_stack
{
	t_list	*a;
	t_list	*b;
	int		flag_v;
	int		flag_b;
	int		max;
	int		bigger;
	int		smaller;
	int		median_a;
	int		median_b;
	int		size_small;
	int		size_bigger;
	t_list	*split_size;
}			t_stack;

typedef struct s_op
{
	const char	*name;
	void		(*f)(t_stack *stacks);
}				t_op;

/*
** COMMON
*/
t_stack	*get_stack_data(int ac, char **av);
void	quit_error(t_stack *stacks, char *line);
void	quit_success(t_stack *stacks, char *msg, char *line);
void	show_stacks_option(t_stack *stacks);

/*
** COMMON - OPERATION
*/
void	op_sa(t_stack *stacks);
void	op_sb(t_stack *stacks);
void	op_ss(t_stack *stacks);
void	op_pa(t_stack *stacks);
void	op_pb(t_stack *stacks);
void	op_ra(t_stack *stacks);
void	op_rb(t_stack *stacks);
void	op_rr(t_stack *stacks);
void	op_rra(t_stack *stacks);
void	op_rrb(t_stack *stacks);
void	op_rrr(t_stack *stacks);

/*
** UTILS
*/
int		get_bigger(t_list *a_b);
int		get_smaller(t_list *a_b);
int		get_median(t_list *a_b, t_stack *stacks, int size);

#endif