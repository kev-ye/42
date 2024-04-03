/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:13:57 by kaye              #+#    #+#             */
/*   Updated: 2021/06/22 15:58:14 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_trunc_fd = O_WRONLY | O_TRUNC | O_CREAT;
static int	g_append_fd = O_WRONLY | O_APPEND | O_CREAT;

static void	create_output_fd(t_list *cmd, int fd_output, int flag_is)
{
	if (flag_is == F_TRUNC)
		fd_output = open(((t_cmd *)cmd->content)->args[0], g_trunc_fd, 0666);
	else if (flag_is == F_APPEND)
		fd_output = open(((t_cmd *)cmd->content)->args[0], g_append_fd, 0666);
	if (fd_output == -1)
		return ;
	else
		close(fd_output);
}

void	create_fd_output(t_list *cmd)
{
	int	first;
	int	fd_output;
	int	fd_input;
	int	flag_is;

	fd_output = -1;
	fd_input = -1;
	flag_is = 0;
	first = 1;
	while (cmd)
	{
		if (first == 1)
			first = 0;
		else if (!first && (flag_is == F_APPEND || flag_is == F_TRUNC))
			create_output_fd(cmd, fd_output, flag_is);
		if (flag_check(cmd) == FLG_EO_CMD)
			break ;
		flag_is = check_for_next(cmd);
		cmd = cmd->next;
	}
}
