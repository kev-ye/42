/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:30:36 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 15:44:13 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_last_cmd(void **cmd, int *fd, int fd_index, t_list *lst_cmd)
{
	t_c_init	last_c;

	last_c = cmd_init();
	if (check_is_redir_cmd(lst_cmd))
	{
		*cmd = get_complete_cmd(*cmd, lst_cmd);
		redir_parser(lst_cmd, &last_c.input_fd, &last_c.output_fd);
	}
	if (last_c.input_fd == -1)
		dup2(fd[fd_index * 2], STDIN_FILENO);
	else
		dup2(fd[fd_index * 2], last_c.input_fd);
	last_c.builtin_status = builtin_exec((t_cmd *)(*cmd));
	if (last_c.builtin_status == NOT_FOUND)
		last_c.lrv = sys_exec(*cmd);
	if (last_c.builtin_status != NOT_FOUND)
		exit(SUCCESS);
	exit(last_c.lrv);
}

void	last_cmd(void *cmd, int *fd, int fd_index, t_list *lst_cmd)
{
	t_c_init	last_c;

	last_c = cmd_init();
	last_c.pid = fork();
	if (last_c.pid < 0)
		exit(PID_FAILURE);
	else if (last_c.pid == 0)
	{
		signal(SIGQUIT, ft_interrupt);
		exec_last_cmd(&cmd, fd, fd_index, lst_cmd);
	}
	else
	{
		waitpid(last_c.pid, &last_c.status, 0);
		close(fd[fd_index * 2]);
	}
	set_lrv(last_c.status);
}
