/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:17:47 by kaye              #+#    #+#             */
/*   Updated: 2021/06/23 17:46:06 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_shell_env(char *new_env, t_list *to_change, int to_add)
{
	if (to_change)
	{
		free(to_change->content);
		to_change->content = (char *)new_env;
	}
	if (to_add == 1)
		ft_lstadd_back(&singleton()->env, ft_lstnew((void *)new_env));
}

static int	cmds_check(char *cmd)
{
	if (!check_space(cmd) && (ft_isalpha(cmd[0]) || cmd[0] == '_'))
		return (1);
	else
		ft_dprintf(STDERR_FILENO, PROG_NAME
			": export: `%s\': not a valid identifier\n", cmd);
	return (0);
}

static void	add_env(char **cmds)
{
	t_list	*to_change;
	char	*new_env;
	int		i;

	i = 1;
	new_env = NULL;
	while (cmds[i])
	{
		if (cmds_check(cmds[i]))
		{
			to_change = search_env(cmds[i], &singleton()->env);
			new_env = ft_strdup(cmds[i]);
			if (!new_env)
				return ;
			if (to_change)
				new_shell_env(new_env, to_change, 0);
			else
				new_shell_env(new_env, NULL, 1);
		}
		++i;
	}
}

static t_list	*env_export(t_list **lst_env)
{
	t_list	*tmp;
	t_list	*new_lst_env;
	char	*env_content;

	new_lst_env = NULL;
	env_content = NULL;
	tmp = *lst_env;
	while (tmp)
	{
		env_content = ft_strdup((char *)tmp->content);
		ft_lstadd_back(&new_lst_env, ft_lstnew((void *)env_content));
		tmp = tmp->next;
	}
	ft_list_sort(&new_lst_env, ft_strcmp);
	add_quote(&new_lst_env);
	return (new_lst_env);
}

int	ft_export(t_cmd *cmds)
{
	t_list	*env_to_print;
	size_t	len_cmds;

	if (!cmds || !cmds->args || !*cmds->args)
		return (ERROR);
	env_to_print = NULL;
	len_cmds = ft_strslen(cmds->args);
	add_env(cmds->args);
	if (len_cmds == 1)
	{
		env_to_print = env_export(&singleton()->env);
		ft_lstprint(env_to_print, '\n');
		ft_lstclear(&env_to_print, free);
	}
	return (SUCCESS);
}
