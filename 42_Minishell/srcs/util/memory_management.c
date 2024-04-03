/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:22:51 by besellem          #+#    #+#             */
/*   Updated: 2021/06/24 18:32:46 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__ft_free_cmds__(void)
{
	const t_list	*tmp = singleton()->lst;
	t_cmd			*cmd;

	while (tmp)
	{
		cmd = tmp->content;
		ft_strsfree(cmd->args_len, cmd->args);
		tmp = tmp->next;
	}
	ft_lstclear(&singleton()->lst, free);
}

void	ft_free_exit(int code)
{
	if (singleton())
	{
		__ft_free_cmds__();
		if (singleton()->prompt)
			ft_memdel((void **)(&singleton()->prompt));
		if (singleton()->cwd)
			ft_memdel((void **)(&singleton()->cwd));
		if (singleton()->env)
			ft_lstclear(&singleton()->env, free);
		if (singleton()->hist.path)
			ft_memdel((void **)(&singleton()->hist.path));
		close(singleton()->hist.fd);
		if (singleton()->option.fd != STDIN_FILENO)
			close(singleton()->option.fd);
		free(singleton());
	}
	if (code != -1)
		exit(code);
}
