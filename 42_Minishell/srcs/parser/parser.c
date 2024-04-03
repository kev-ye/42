/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 22:02:00 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 16:08:00 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_parsing(t_parsing *p, t_list **cmds, char **s)
{
	ft_bzero(p, sizeof(t_parsing));
	ft_lstclear(cmds, free);
	quotes2close(0, &p->quotes, QUOTES_RESET_FLAG);
	p->s = *s;
}

t_cmd	*new_cmd(uint16_t status, t_list **args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (ft_error(ERR_MALLOC, __FILE__, __LINE__));
	cmd->args = ft_lst2strs(args);
	ft_lstclear(args, free);
	cmd->args_len = ft_strslen(cmd->args);
	cmd->status_flag = status;
	return (cmd);
}

void	ft_parse(char *s)
{
	t_parsing	p;
	size_t		i;

	init_parsing(&p, &singleton()->lst, &s);
	i = 0;
	while (p.s[i])
	{
		if (__pass_spaces__(&p, &i))
			break ;
		if (__check_str_limit__(&p, &i))
			continue ;
		if (FALSE == __backslash_case__(&p, &i))
		{
			if (FALSE == __handle_quotes__(&p, &i)
				&& FALSE == __handle_variable_expansion__(&p, &i))
				++i;
		}
		__need_to_subdivide_command__(&p, &i);
	}
	__fill_last_command__(&p, &i);
}

/*
TESTS TO DO:

ls -la; echo bonjour >> out; ls | grep srcs ;
ls -la; ec"ho" bo"njo"ur >> out ;echo ' bonjour "" "a\" $LESS\toi'\"\' > out
ls -la; ec"ho" bo"njo"ur >> out ;echo " bonjour '' 'a\' $LESS\toi"\"\' > out
*/
