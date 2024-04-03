/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:06:04 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 14:39:48 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	g_builtin[] = {
	{"echo", ft_echo, NULL},
	{"cd", ft_cd, NULL},
	{"pwd", NULL, ft_pwd},
	{"env", ft_env, NULL},
	{"unset", ft_unset, NULL},
	{"export", ft_export, NULL},
	{"exit", ft_exit, NULL},
	{"clear", NULL, ft_clear},
	{NULL, NULL, NULL}
};

static int	ft_exec_builtin_cmd(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (g_builtin[i].cmd)
	{
		if (cmds && FALSE == ft_strcmp(cmds->args[0], g_builtin[i].cmd))
		{
			if (!g_builtin[i].f1)
				return (g_builtin[i].f2());
			else
				return (g_builtin[i].f1(cmds));
		}
		++i;
	}
	return (NOT_FOUND);
}

int	builtin_exec(t_cmd *cmds)
{
	int	ret;

	if (!check_if_path_exist(singleton()->env)
		&& !ft_strcmp(cmds->args[0], "env"))
		return (NOT_FOUND);
	ret = ft_exec_builtin_cmd(cmds);
	if (!ft_strcmp(cmds->args[0], ".."))
	{
		ft_dprintf(STDERR_FILENO, PROG_NAME": %s: command not found\n",
			cmds->args[0]);
		ret = LRV_CMD_NOT_FOUND;
	}
	if (NOT_FOUND == ret)
		return (ret);
	singleton()->lrv = ret;
	return (SUCCESS);
}
