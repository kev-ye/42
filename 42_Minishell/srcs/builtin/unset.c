/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:17:36 by kaye              #+#    #+#             */
/*   Updated: 2021/06/24 14:37:36 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_and_swap(t_list **head, t_list **env, t_list **prev)
{
	t_list	*current;

	current = *env;
	if (*prev)
	{
		*env = *prev;
		(*env)->next = current->next;
	}
	else
		*head = current->next;
	ft_memdel((void **)&current->content);
	ft_lstdelone(current, NULL);
}

static void	del_env(t_list *lst_env, size_t len, char *cmd)
{
	t_list	*prev;

	prev = NULL;
	while (lst_env)
	{
		if (!ft_strncmp(lst_env->content, cmd, len)
			&& '=' == ((char *)(lst_env->content))[len])
		{
			del_and_swap(&singleton()->env, &lst_env, &prev);
			prev = lst_env;
			lst_env = lst_env->next;
		}
		else
		{
			prev = lst_env;
			lst_env = lst_env->next;
		}
	}
}

static int	cmds_check(char *cmd)
{
	if (!check_space(cmd) && (ft_isalpha(cmd[0]) || cmd[0] == '_'))
		return (1);
	else
		ft_dprintf(STDERR_FILENO, PROG_NAME
			": unset: `%s\': not a valid identifier\n", cmd);
	return (0);
}

static void	to_unset(char **cmds)
{
	int	i;

	i = 1;
	while (cmds && cmds[i])
	{
		if (cmds_check(cmds[i]))
			del_env(singleton()->env, ft_strlen(cmds[i]), cmds[i]);
		++i;
	}
}

int	ft_unset(t_cmd *cmds)
{
	if (!cmds || !cmds->args || !*cmds->args)
		return (ERROR);
	if (!*(cmds->args + 1))
		return (SUCCESS);
	to_unset(cmds->args);
	return (SUCCESS);
}
