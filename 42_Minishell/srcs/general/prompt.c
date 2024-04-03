/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:02:48 by besellem          #+#    #+#             */
/*   Updated: 2021/06/24 18:33:21 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_prompt(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		if (singleton()->prompt)
			ft_memdel((void **)(&singleton()->prompt));
		ft_memdel((void **)(&singleton()->cwd));
		singleton()->cwd = pwd;
		singleton()->cwd_basename = ft_strrchr(singleton()->cwd, '/');
		if (*(singleton()->cwd_basename + 1))
			singleton()->cwd_basename++;
		ft_asprintf(&singleton()->prompt, PROMPT, singleton()->cwd_basename);
	}
}

void	prompt(void)
{
	char	*ret;
	int		gnl_check;

	gnl_check = TRUE;
	while (TRUE)
	{
		ft_bzero(&singleton()->edit, sizeof(t_edition));
		update_prompt();
		if (STDIN_FILENO == singleton()->option.fd && singleton()->isatty_stdin)
		{
			singleton()->rl_lvl = 1;
			ret = readline(singleton()->prompt);
		}
		else
			gnl_check = get_next_line(singleton()->option.fd, &ret);
		if (!ret)
			ft_interrupt(SIGQUIT);
		if (singleton()->isatty_stdin)
			add2history(ret);
		ft_parse(ret);
		ft_exec_each_cmd(singleton()->lst);
		__ft_free_cmds__();
		if (NULL == ft_memdel((void **)(&ret)) && gnl_check <= 0)
			ft_exit_for_prompt();
	}
}
