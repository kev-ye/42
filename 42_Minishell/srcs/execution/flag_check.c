/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:37:33 by kaye              #+#    #+#             */
/*   Updated: 2021/06/15 00:04:40 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_check(t_list *lst_cmd)
{
	if (lst_cmd && (((t_cmd *)lst_cmd->content)->status_flag & FLG_EOL))
		return (FLG_EOL);
	else if (lst_cmd && (((t_cmd *)lst_cmd->content)->status_flag & FLG_EO_CMD))
		return (FLG_EO_CMD);
	else if (lst_cmd && (((t_cmd *)lst_cmd->content)->status_flag & FLG_PIPE))
		return (FLG_PIPE);
	else if (lst_cmd && (((t_cmd *)lst_cmd->content)->status_flag & FLG_APPEND))
		return (FLG_APPEND);
	else if (lst_cmd && (((t_cmd *)lst_cmd->content)->status_flag & FLG_INPUT))
		return (FLG_INPUT);
	else if (lst_cmd && (((t_cmd *)lst_cmd->content)->status_flag & FLG_OUTPUT))
		return (FLG_OUTPUT);
	else if (lst_cmd && (((t_cmd *)lst_cmd->content)->status_flag & FLG_DINPUT))
		return (FLG_DINPUT);
	return (NO_ONE);
}

int	is_redir(t_list *lst_cmd)
{
	if (lst_cmd && ((((t_cmd *)lst_cmd->content)->status_flag & FLG_OUTPUT)
			|| (((t_cmd *)lst_cmd->content)->status_flag & FLG_APPEND)
			|| (((t_cmd *)lst_cmd->content)->status_flag & FLG_INPUT)
			|| (((t_cmd *)lst_cmd->content)->status_flag & FLG_DINPUT)))
	{
		return (1);
	}
	return (0);
}

int	is_sep_or_end(t_list *lst_cmd)
{
	if (lst_cmd && ((((t_cmd *)lst_cmd->content)->status_flag & FLG_EO_CMD)
			|| (((t_cmd *)lst_cmd->content)->status_flag & FLG_EOL)))
		return (1);
	return (0);
}
