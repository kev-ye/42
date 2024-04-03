/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:38:17 by kaye              #+#    #+#             */
/*   Updated: 2021/06/21 19:26:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_quote_if(char **env_head,
	char **new_env,
	char **tmp_env,
	t_list **tmp)
{
	*env_head = head_env((char *)(*tmp)->content);
	if (!*env_head)
		return ;
	ft_asprintf(&(*new_env), "declare -x %s\"%s\"", *env_head, (*tmp_env) + 1);
	if (!new_env && ft_memdel((void **)(&(*env_head))) == NULL)
		return ;
	free(*env_head);
	free((*tmp)->content);
	(*tmp)->content = *new_env;
}

static void	add_quote_else(char **env_head,
	char **new_env,
	t_list **tmp)
{
	*env_head = head_env((char *)(*tmp)->content);
	if (!*env_head)
		return ;
	ft_asprintf(&(*new_env), "declare -x %s", *env_head);
	if (!*new_env && ft_memdel((void **)(&(*env_head))) == NULL)
		return ;
	free(*env_head);
	free((*tmp)->content);
	(*tmp)->content = *new_env;
}

void	add_quote(t_list **lst_env)
{
	t_list	*tmp;
	char	*new_env;
	char	*tmp_env;
	char	*env_head;

	tmp = *lst_env;
	env_head = NULL;
	tmp_env = NULL;
	new_env = NULL;
	while (tmp)
	{
		tmp_env = ft_strchr((char *)tmp->content, '=');
		if (tmp_env != NULL)
			add_quote_if(&env_head, &new_env, &tmp_env, &tmp);
		else
			add_quote_else(&env_head, &new_env, &tmp);
		tmp = tmp->next;
	}
}

int	check_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=')
	{
		if (s[i] == ' ')
			return (1);
		++i;
	}
	return (0);
}

char	*head_env(char *env)
{
	char	*env_head;
	int		len;

	len = 0;
	env_head = NULL;
	while (env[len] && env[len] != '=')
		++len;
	if (env[len] && env[len] == '=')
	{
		env_head = ft_calloc(len + 2, sizeof(char));
		if (!env_head)
			return (NULL);
		ft_memcpy(env_head, env, len + 1);
	}
	else
	{
		env_head = ft_calloc(len, sizeof(char));
		if (!env_head)
			return (NULL);
		ft_memcpy(env_head, env, len + 1);
	}
	return (env_head);
}
