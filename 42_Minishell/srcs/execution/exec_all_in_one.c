/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_in_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:03:54 by kaye              #+#    #+#             */
/*   Updated: 2021/06/26 23:20:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_aio
{
	t_list	*tmp;
	int		*fd;
	int		pipe_len;
}	t_aio;

static void	cmd_with_multi_flag(t_list *lst_cmd, int *fd)
{
	t_list	*tmp;
	int		fd_index;

	tmp = lst_cmd;
	fd_index = 0;
	while (tmp && (is_redir(tmp) || flag_check(tmp) == FLG_PIPE))
	{
		if (!check_is_inter(tmp))
			break ;
		interm_cmd(tmp->content, fd, fd_index, tmp);
		while (tmp && is_redir(tmp))
			tmp = tmp->next;
		++fd_index;
		tmp = tmp->next;
	}
	last_cmd(tmp->content, fd, fd_index, tmp);
}

static void	exec_multi_flag_cmd(t_list *tmp, int pipe_len, int *fd)
{
	if (pipe_len > 0)
	{
		cmd_with_multi_flag(tmp->next, fd);
		if (fd)
			free(fd);
	}
}

void	all_in_one(t_list *lst_cmd)
{
	t_aio	aio;

	aio.tmp = lst_cmd;
	aio.fd = NULL;
	if (aio.tmp && builtin_cmd_with_redir(aio.tmp->content, lst_cmd))
		return ;
	if (aio.tmp && (flag_check(aio.tmp) == FLG_EO_CMD
			|| flag_check(aio.tmp) == FLG_EOL))
	{
		simple_cmd(aio.tmp->content);
		return ;
	}
	aio.pipe_len = count_pipe(aio.tmp);
	if (aio.pipe_len > 0)
	{
		aio.fd = malloc(sizeof(int) * (aio.pipe_len * 2));
		if (!aio.fd)
			return ;
		pipe(aio.fd);
	}
	create_fd_output(lst_cmd);
	first_cmd(aio.tmp->content, aio.fd, aio.tmp, aio.pipe_len);
	while (aio.tmp && is_redir(aio.tmp))
		aio.tmp = aio.tmp->next;
	exec_multi_flag_cmd(aio.tmp, aio.pipe_len, aio.fd);
}

void	exec_all_in_one(t_list *lst_cmd)
{
	if (!lst_cmd)
		return ;
	if (!((t_cmd *)lst_cmd->content)->args && check_is_redir_cmd(lst_cmd))
		lst_cmd->content = get_complete_cmd(lst_cmd->content, lst_cmd);
	if (!((t_cmd *)lst_cmd->content)->args)
		return ;
	all_in_one(lst_cmd);
}
