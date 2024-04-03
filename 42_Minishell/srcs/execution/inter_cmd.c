/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:30:36 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 15:44:23 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_inter_cmd(void **cmd, int *fd, int fd_index, t_list *lst_cmd)
{
	t_c_init	inter_c;

	inter_c = cmd_init();
	if (check_is_redir_cmd(lst_cmd))
	{
		*cmd = get_complete_cmd(*cmd, lst_cmd);
		redir_parser(lst_cmd, &inter_c.input_fd, &inter_c.output_fd);
	}
	if (inter_c.input_fd == -1)
		dup2(fd[fd_index * 2], STDIN_FILENO);
	else
		dup2(fd[fd_index * 2], inter_c.input_fd);
	if (inter_c.output_fd == -1)
		dup2(fd[((fd_index + 1) * 2) + 1], STDOUT_FILENO);
	else
		dup2(fd[((fd_index + 1) * 2) + 1], inter_c.output_fd);
	inter_c.builtin_status = builtin_exec((t_cmd *)(*cmd));
	if (inter_c.builtin_status == NOT_FOUND)
		inter_c.lrv = sys_exec(*cmd);
	if (inter_c.builtin_status != NOT_FOUND)
		exit(SUCCESS);
	exit(inter_c.lrv);
}

void	interm_cmd(void *cmd, int *fd, int fd_index, t_list *lst_cmd)
{
	t_c_init	inter_c;

	inter_c = cmd_init();
	pipe(fd + ((fd_index + 1) * 2));
	inter_c.pid = fork();
	if (inter_c.pid < 0)
		exit(PID_FAILURE);
	else if (inter_c.pid == 0)
	{
		signal(SIGQUIT, ft_interrupt);
		exec_inter_cmd(&cmd, fd, fd_index, lst_cmd);
	}
	else
	{
		waitpid(inter_c.pid, &inter_c.status, 0);
		close(fd[((fd_index + 1) * 2) + 1]);
		close(fd[fd_index * 2]);
	}
	set_lrv(inter_c.status);
}
