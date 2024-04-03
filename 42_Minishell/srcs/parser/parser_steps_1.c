/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_steps_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:58:10 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 16:17:23 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct s_redirections	g_limits[] = {
	{";", 1, FLG_EO_CMD},
	{"|", 1, FLG_PIPE},
	{">>", 2, FLG_APPEND},
	{">", 1, FLG_OUTPUT},
	{"<<", 2, FLG_DINPUT},
	{"<", 1, FLG_INPUT},
	{NULL, 0, 0}
};

static int	found_str_limit(char *s, size_t i, t_list **args)
{
	t_cmd	*new;
	size_t	k;

	k = 0;
	while (g_limits[k].redir)
	{
		if (0 == ft_strncmp(s + i, g_limits[k].redir, g_limits[k].len))
		{
			if (i > 0)
				ft_lstadd_back(args, ft_lstnew(ft_substr(s, 0, i)));
			new = new_cmd(g_limits[k].flag, args);
			ft_lstadd_back(&singleton()->lst, ft_lstnew(new));
			return (g_limits[k].len);
		}
		++k;
	}
	return (0);
}

int	__pass_spaces__(t_parsing *p, size_t *i)
{
	while (p->s[*i] && ft_incharset(SPACES, p->s[*i])
		&& FALSE == p->quotes.first)
	{
		p->s++;
	}
	return ('\0' == p->s[*i]);
}

int	__check_str_limit__(t_parsing *p, size_t *i)
{
	if (FALSE == p->quotes.first)
	{
		p->limit = found_str_limit(p->s, *i, &p->args);
		if (p->limit)
		{
			quotes2close(0, &p->quotes, QUOTES_RESET_FLAG);
			p->s += *i + p->limit;
			*i = 0;
			return (TRUE);
		}
	}
	return (FALSE);
}

int	__backslash_case__(t_parsing *p, size_t *i)
{
	if ('\\' == p->s[*i])
	{
		if ((p->quotes.first && p->quotes.d_quote
				&& ft_incharset(SPEC_CHARS2, p->s[*i + 1]))
			|| FALSE == p->quotes.first)
		{
			ft_strnclean(p->s + *i, "\\", 1);
		}
		if (ft_incharset(SPEC_CHARS, p->s[*i]))
			++(*i);
		return (TRUE);
	}
	return (FALSE);
}

int	__handle_quotes__(t_parsing *p, size_t *i)
{
	quotes2close(p->s[*i], &p->quotes, QUOTES_SET_FLAG);
	if ((('"' == p->s[*i]) || ('\'' == p->s[*i])) && p->quotes.did_change)
	{
		ft_strnclean(p->s + *i, QUOTES, 1);
		if (!ft_incharset(QUOTES, p->s[*i]))
			quotes2close(p->s[*i], &p->quotes, QUOTES_SET_FLAG);
		if ((p->quotes.did_change && !ft_incharset(QUOTES, p->s[*i]))
			|| (!p->quotes.did_change && !p->s[*i]))
		{
			ft_lstadd_back(&p->args, ft_lstnew(ft_substr(p->s, 0, *i)));
			p->s += *i;
			*i = 0;
		}
		return (TRUE);
	}
	return (FALSE);
}
