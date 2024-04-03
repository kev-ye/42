/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:17:45 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 14:39:48 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_neg_strdigit(char *s)
{
	return (s && !ft_strncmp(s, "-", 1) && ft_strisdigit(s + 1));
}

static int	print_arg_error(t_cmd *cmds)
{
	ft_dprintf(STDERR_FILENO,
		PROG_NAME": %s: too many arguments\n", cmds->args[0]);
	singleton()->lrv = LRV_GENERAL_ERROR;
	return (LRV_GENERAL_ERROR);
}

static void	print_num_arg_error(t_cmd *cmds, int *ret_no_num)
{
	ft_dprintf(STDERR_FILENO,
		PROG_NAME": %s: %s: numeric argument required\n",
		cmds->args[0], cmds->args[1]);
	*ret_no_num = 1;
}

int	ft_exit(t_cmd *cmds)
{
	size_t	len;
	uint8_t	ret;
	int		ret_no_num;

	ret = 0;
	ret_no_num = 0;
	len = ft_strslen(cmds->args);
	ft_putstr_fd("exit\n", STDIN_FILENO);
	if (len > 2 && cmds->args[1] && (ft_strisdigit(cmds->args[1]) == 1
			|| check_neg_strdigit(cmds->args[1])))
		return (print_arg_error(cmds));
	else if (len >= 2 && cmds->args[1]
		&& ft_strisdigit(cmds->args[1]) == 0
		&& !check_neg_strdigit(cmds->args[1]))
		print_num_arg_error(cmds, &ret_no_num);
	if (ft_strisdigit(cmds->args[1]) || check_neg_strdigit(cmds->args[1]))
		ret = (uint8_t)ft_atoi(cmds->args[1]);
	if (ret_no_num == 1)
		ret = NO_NUM_ARG;
	ft_free_exit(-1);
	exit(ret);
}

void	ft_exit_for_prompt(void)
{
	if (singleton()->isatty_stdin)
		ft_putstr_fd("exit\n", STDIN_FILENO);
	ft_free_exit(SUCCESS);
}
