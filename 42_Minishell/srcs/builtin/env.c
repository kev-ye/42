/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:17:43 by kaye              #+#    #+#             */
/*   Updated: 2021/06/23 17:10:41 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_path_exist(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if ((char *)tmp->content
			&& !ft_strncmp((char *)tmp->content, "PATH=", 5))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	show_env(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strchr((char *)tmp->content, '='))
			ft_dprintf(STDOUT_FILENO, "%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

int	ft_env(t_cmd *cmds)
{
	int	len_cmd;
	int	i;

	i = 0;
	if (!cmds || !cmds->args || !*cmds->args)
		return (ERROR);
	while (cmds->args[i])
		++i;
	len_cmd = i;
	i = 0;
	if (len_cmd == 1)
		show_env(&singleton()->env);
	return (SUCCESS);
}
