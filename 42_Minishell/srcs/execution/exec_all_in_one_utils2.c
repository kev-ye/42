/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_in_one_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:30:36 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 14:39:48 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_completing2(void **cmd, char ***new_cmd)
{
	ft_strsfree(((t_cmd *)(*cmd))->args_len, ((t_cmd *)(*cmd))->args);
	((t_cmd *)(*cmd))->args = *new_cmd;
	((t_cmd *)(*cmd))->args_len = ft_strslen(((t_cmd *)(*cmd))->args);
}

static void	cmd_completing(void **cmd,
	t_list *lst_tmp,
	char ***new_cmd,
	int len)
{
	int	i;
	int	j;

	len += ft_strslen(((t_cmd *)(*cmd))->args);
	*new_cmd = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!*new_cmd)
		return ;
	i = 0;
	while (((t_cmd *)(*cmd))->args && ((t_cmd *)(*cmd))->args[i])
	{
		(*new_cmd)[i] = ft_strdup(((t_cmd *)(*cmd))->args[i]);
		++i;
		--len;
	}
	j = 1;
	while (((t_cmd *)lst_tmp->content)->args[j] && len)
	{
		(*new_cmd)[i] = ft_strdup(((t_cmd *)lst_tmp->content)->args[j]);
		ft_memdel((void **)&((t_cmd *)lst_tmp->content)->args[j]);
		++i;
		++j;
		--len;
	}
	cmd_completing2(cmd, new_cmd);
}

void	*get_complete_cmd(void *cmd, t_list *lst_cmd)
{
	t_list	*lst_tmp;
	size_t	len;
	char	**new_cmd;

	lst_tmp = lst_cmd->next;
	len = 0;
	new_cmd = NULL;
	while (lst_tmp)
	{
		if (((t_cmd *)lst_tmp->content)->args)
			len = ft_strslen(((t_cmd *)lst_tmp->content)->args);
		if (lst_tmp && ((t_cmd *)lst_tmp->content)->args && len > 1)
			cmd_completing(&cmd, lst_tmp, &new_cmd, len);
		if (!is_redir(lst_tmp))
			break ;
		lst_tmp = lst_tmp->next;
	}
	return (cmd);
}

t_c_init	cmd_init(void)
{
	t_c_init	c_init;

	c_init.status = 1;
	c_init.builtin_status = 1;
	c_init.input_fd = -1;
	c_init.output_fd = -1;
	c_init.lrv = 0;
	return (c_init);
}

void	set_lrv(int status)
{
	if (_wifexited(status) != 0)
		singleton()->lrv = _wexitstatus(status);
	else if (_wifsignaled(status) == 1)
	{
		if (_wtermsig(status) == SIGQUIT)
			printf("Quit: %d\n", SIGQUIT);
		if (_wtermsig(status) == SIGINT)
			printf("\n");
		singleton()->lrv = LRV_KILL_SIG + _wtermsig(status);
	}
}
