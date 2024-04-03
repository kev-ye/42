/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:17:59 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 13:19:36 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_env(char **env)
{
	t_list	*new_env;
	t_list	*tmp;
	void	*ptr;
	int		i;

	new_env = NULL;
	i = 0;
	while (env[i])
	{
		if (env[i] && 0 == ft_strncmp(env[i], "OLDPWD=", 7) && ++i)
			continue ;
		ptr = ft_strdup(env[i++]);
		tmp = ft_lstnew(ptr);
		if (!ptr || !tmp)
		{
			if (ptr)
				ft_memdel((void **)&ptr);
			if (tmp)
				ft_memdel((void **)&tmp);
			ft_lstclear(&new_env, free);
			return (ft_error(ERR_MALLOC, __FILE__, __LINE__));
		}
		ft_lstadd_back(&new_env, tmp);
	}
	return (new_env);
}

static char	*ft_get_shlvl(char *shlvl)
{
	char	*ret;
	int		level;

	if (!shlvl)
		return (ft_strdup("SHLVL=1"));
	level = ft_atoi(shlvl);
	if (ft_strlen(shlvl) > (size_t)ft_nblen(INT32_MAX) || (level + 1) < 0)
		level = 0;
	else if (999 == level)
		return (ft_strdup("SHLVL="));
	else if (level >= 1000)
	{
		ft_dprintf(STDERR_FILENO,
			PROG_NAME ": warning: shell level (%ld) too high, resetting to 1\n",
			level + 1);
		level = 1;
	}
	else
		++level;
	ft_asprintf(&ret, "SHLVL=%d", level);
	if (!ret && NULL == ft_memdel((void **)&shlvl))
		return (ft_error(ERR_MALLOC, __FILE__, __LINE__));
	return (ret);
}

int	ft_init_minishell(char **env)
{
	const char	*args[] = {"export", NULL, NULL};
	const t_cmd	cmd = {.args = (char **)args, .args_len = 0, .status_flag = 0};
	char		*ret;
	char		*shlvl;

	if (NULL == singleton())
		return ((int)ft_error(ERR_MALLOC, __FILE__, __LINE__));
	singleton()->env = get_env(env);
	shlvl = ft_getenv("SHLVL");
	ret = ft_get_shlvl(shlvl);
	args[1] = ret;
	ft_export((t_cmd *)&cmd);
	ft_memdel((void **)&ret);
	ft_memdel((void **)&shlvl);
	singleton()->isatty_stdin = isatty(STDIN_FILENO);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_interrupt);
	return (1);
}
