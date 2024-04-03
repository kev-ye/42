/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:07:20 by kaye              #+#    #+#             */
/*   Updated: 2021/06/23 15:15:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sys_exec_msg_error(t_cmd *cmds)
{
	struct stat	buf;

	if (cmds->args)
		lstat(cmds->args[0], &buf);
	if (check_if_path_exist(singleton()->env))
	{
		ft_dprintf(STDERR_FILENO,
			PROG_NAME": %s: command not found\n", cmds->args[0]);
		return (LRV_CMD_NOT_FOUND);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		ft_dprintf(STDERR_FILENO,
			PROG_NAME": %s: is a directory\n", cmds->args[0]);
		return (LRV_PERMISSION);
	}
	else
	{
		ft_dprintf(STDERR_FILENO,
			PROG_NAME": %s: %s\n", cmds->args[0], strerror(errno));
		if (13 == errno)
			return (LRV_PERMISSION);
		else
			return (LRV_CMD_NOT_FOUND);
	}
}

static int	ft_exec_cmd(char *file, t_cmd *cmds)
{
	char	**env;
	int		ret;
	int		lrv;

	ret = 0;
	lrv = 0;
	env = ft_lst2strs(&singleton()->env);
	ret = execve(file, cmds->args, env);
	lrv = sys_exec_msg_error(cmds);
	if (ret == -1)
		ft_strsfree(ft_strslen(env), env);
	return (lrv);
}

int	sys_exec(void *ptr)
{
	t_cmd	*cmd;
	char	*ex;
	int		not_found;
	int		lrv;

	cmd = ptr;
	not_found = 0;
	lrv = 0;
	if (!cmd->args || !cmd->args)
		return (EXEC_FAILURE);
	ex = search_executable(cmd->args[0]);
	lrv = ft_exec_cmd(ex, cmd);
	ft_memdel((void **)&ex);
	if (not_found == 1)
		exit(LRV_CMD_NOT_FOUND);
	return (lrv);
}
