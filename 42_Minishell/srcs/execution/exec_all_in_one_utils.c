/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_in_one_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:30:36 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 16:04:45 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_inter(t_list *lst_cmd)
{
	while (lst_cmd && is_redir(lst_cmd))
		lst_cmd = lst_cmd->next;
	if (flag_check(lst_cmd) == FLG_EO_CMD || flag_check(lst_cmd) == FLG_EOL)
		return (0);
	return (1);
}

int	check_is_redir_cmd(t_list *lst_cmd)
{
	if (lst_cmd && is_redir(lst_cmd))
		return (1);
	return (0);
}

int	check_have_dinput(t_list *lst_cmd)
{
	int	is_dinput;

	is_dinput = 0;
	while (lst_cmd)
	{
		if (flag_check(lst_cmd) == FLG_PIPE)
			break ;
		if (flag_check(lst_cmd) == FLG_DINPUT)
			is_dinput = 1;
		lst_cmd = lst_cmd->next;
	}
	return (is_dinput);
}

int	count_pipe(t_list *lst_cmd)
{
	t_list	*tmp;
	int		count;

	tmp = lst_cmd;
	count = 0;
	while (tmp && (flag_check(tmp) != FLG_EO_CMD || flag_check(tmp) != FLG_EOL))
	{
		if (flag_check(tmp) == FLG_PIPE)
			++count;
		tmp = tmp->next;
	}
	return (count);
}
