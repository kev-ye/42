/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_with_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:28:00 by kaye              #+#    #+#             */
/*   Updated: 2021/06/26 23:36:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_spl_c
{
	pid_t	pid;
	int		status;
	int		lrv;
}	t_spl_c;

static t_builtin	g_builtin[] = {
	{"cd", ft_cd, NULL},
	{"unset", ft_unset, NULL},
	{"export", ft_export, NULL},
	{"exit", ft_exit, NULL},
	{NULL, NULL, NULL}
};

static int	ft_check_builtin_cmd(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (g_builtin[i].cmd)
	{
		if (cmds && FALSE == ft_strcmp(cmds->args[0], g_builtin[i].cmd))
			return (FOUND);
		++i;
	}
	return (NOT_FOUND);
}

static int	builtin_redir_cmd(void *cmd, t_list *lst_cmd)
{
	t_spl_c		spl_c;
	t_c_init	spl_c_r;

	spl_c_r = cmd_init();
	spl_c.status = 1;
	cmd = get_complete_cmd(cmd, lst_cmd);
	if (ft_check_builtin_cmd((t_cmd *)cmd) == NOT_FOUND)
		return (0);
	else
	{
		create_fd_output(lst_cmd);
		if (builtin_redir_parser(lst_cmd,
				&spl_c_r.input_fd, &spl_c_r.output_fd) == ERROR)
			return (1);
		builtin_exec((t_cmd *)cmd);
	}
	return (1);
}

int	builtin_cmd_with_redir(void *cmd, t_list *lst_cmd)
{
	t_list	*tmp;

	tmp = lst_cmd;
	while (tmp && tmp->next && check_is_redir_cmd(tmp))
		tmp = tmp->next;
	if (flag_check(tmp) == FLG_EOL)
	{
		if (!builtin_redir_cmd(cmd, lst_cmd))
			return (0);
		return (1);
	}
	return (0);
}
