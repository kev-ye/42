/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:30:36 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 18:36:30 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_first_cmd(void **cmd, int *fd, t_list *lst_cmd, int pipe_len)
{
	t_c_init	first_c;

	first_c = cmd_init();
	if (check_is_redir_cmd(lst_cmd))
	{
		*cmd = get_complete_cmd(*cmd, lst_cmd);
		redir_parser(lst_cmd, &first_c.input_fd, &first_c.output_fd);
	}
	if (pipe_len > 0)
	{
		if (first_c.output_fd == -1)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(fd[1], first_c.output_fd);
	}
	first_c.builtin_status = builtin_exec((t_cmd *)(*cmd));
	if (first_c.builtin_status == NOT_FOUND)
		first_c.lrv = sys_exec(*cmd);
	if (first_c.builtin_status != NOT_FOUND)
		exit(SUCCESS);
	exit(first_c.lrv);
}

void	first_cmd(void *cmd, int *fd, t_list *lst_cmd, int pipe_len)
{
	t_c_init	first_c;

	first_c = cmd_init();
	first_c.pid = fork();
	if (first_c.pid < 0)
		exit(PID_FAILURE);
	else if (first_c.pid == 0)
	{
		signal(SIGQUIT, ft_interrupt);
		exec_first_cmd(&cmd, fd, lst_cmd, pipe_len);
	}
	else
	{
		waitpid(first_c.pid, &first_c.status, 0);
		if (fd)
			close(fd[1]);
	}
	set_lrv(first_c.status);
}
