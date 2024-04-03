/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:45:35 by kaye              #+#    #+#             */
/*   Updated: 2021/06/21 19:57:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_pipe(t_list *lst_cmd)
{
	t_list	*tmp;
	int		ret;

	tmp = lst_cmd;
	ret = -1;
	while (tmp)
	{
		if (((t_cmd *)tmp->content)->status_flag & FLG_PIPE)
		{
			ret = (int)((t_cmd *)tmp->content)->status_flag;
			tmp = tmp->next;
		}
		else
			break ;
	}
	if (ret != -1
		&& ((((t_cmd *)tmp->content)->status_flag & FLG_EOL)
			|| (((t_cmd *)tmp->content)->status_flag & FLG_EO_CMD)))
		return (ONLY_PIPE);
	return (-1);
}

static int	only_redir(t_list *lst_cmd)
{
	t_list	*tmp;
	int		ret;

	tmp = lst_cmd;
	ret = -1;
	while (tmp)
	{
		if ((((t_cmd *)tmp->content)->status_flag & FLG_INPUT)
			|| (((t_cmd *)tmp->content)->status_flag & FLG_OUTPUT)
			|| (((t_cmd *)tmp->content)->status_flag & FLG_APPEND)
			|| (((t_cmd *)tmp->content)->status_flag & FLG_DINPUT))
		{
			ret = (int)((t_cmd *)tmp->content)->status_flag;
			tmp = tmp->next;
		}
		else
			break ;
	}
	if (ret != -1 && ((((t_cmd *)tmp->content)->status_flag & FLG_EOL)
			|| (((t_cmd *)tmp->content)->status_flag & FLG_EO_CMD)))
		return (ONLY_REDIR);
	return (-1);
}

int	part_cmd_check(t_list *lst_cmd)
{
	t_list	*tmp;
	int		ret_only_pipe;
	int		ret_only_redir;

	tmp = lst_cmd;
	ret_only_pipe = only_pipe(lst_cmd);
	ret_only_redir = only_redir(lst_cmd);
	if (ret_only_pipe == -1 && ret_only_redir == -1
		&& (!(((t_cmd *)tmp->content)->status_flag & FLG_EO_CMD)
			|| !(((t_cmd *)tmp->content)->status_flag & FLG_EOL)))
		return (MIX);
	else if (ret_only_pipe != -1)
		return (ONLY_PIPE);
	else if (ret_only_redir != -1)
		return (ONLY_REDIR);
	return (-1);
}
