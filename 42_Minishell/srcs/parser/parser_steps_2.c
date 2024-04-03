/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_steps_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:58:16 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 16:06:46 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_variable(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (NOT_FOUND);
	if ((!ft_isalnum(s[i]) && s[i] != '_') || ft_isdigit(s[i]))
		return (NOT_FOUND);
	++i;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		++i;
	if (!s[i] || !(ft_isalnum(s[i]) || s[i] == '_'))
		return (i);
	else
		return (NOT_FOUND);
}

static int	get_env_var(char **s, size_t i)
{
	const int	len_str = len_variable(*s + i);
	t_list		*tmp;
	char		*p;
	char		*ptr;
	char		*new;

	if (NOT_FOUND == len_str)
		return (0);
	p = ft_substr(*s, (unsigned int)i, len_str);
	if (!p)
		return ((size_t)ft_error(ERR_MALLOC, __FILE__, __LINE__));
	ptr = NULL;
	tmp = search_env(p, &singleton()->env);
	if (tmp)
		ptr = ft_strchr(tmp->content, '=');
	new = ft_calloc(ft_strlen(*s) + ft_strlen(ptr) - len_str + 1, sizeof(char));
	if (!new)
		return ((size_t)ft_error(ERR_MALLOC, __FILE__, __LINE__));
	ft_memcpy(new, *s, i - 1);
	if (ptr && ptr + 1)
		ft_memcpy(new + i - 1, ptr + 1, ft_strlen(ptr) - 1);
	ft_strcat(new, *s + i + len_str);
	*s = new;
	return (ft_trni((ptr != NULL), (int)ft_strlen(ptr) - 1, 0) - 1);
}

int	__handle_variable_expansion__(t_parsing *p, size_t *i)
{
	void	*lst_ptr;

	if ((FALSE == p->quotes.first || p->quotes.d_quote) && '$' == p->s[*i])
	{
		lst_ptr = (void *)ft_lstlast(singleton()->lst);
		if (lst_ptr)
			lst_ptr = ((t_list *)lst_ptr)->content;
		if (FALSE == p->quotes.first && ft_incharset(QUOTES, p->s[*i + 1]))
			ft_strnclean(p->s + *i, "$", 1);
		else if (!singleton()->lst
			|| !(((t_cmd *)lst_ptr)->status_flag & FLG_DINPUT))
		{
			if ('?' == p->s[*i + 1])
			{
				ft_strnclean(p->s, "$", 1);
				p->s[(*i)++] = LRV_REPLACEMENT;
			}
			else
				*i += get_env_var(&p->s, *i + 1) + 1;
		}
		else
			++(*i);
		return (TRUE);
	}
	return (FALSE);
}

int	__need_to_subdivide_command__(t_parsing *p, size_t *i)
{
	if (ft_incharset(SPACES, p->s[*i]) && FALSE == p->quotes.first)
	{
		ft_lstadd_back(&p->args, ft_lstnew(ft_substr(p->s, 0, *i)));
		p->s += *i;
		*i = 0;
		return (TRUE);
	}
	return (FALSE);
}

int	__fill_last_command__(t_parsing *p, size_t *i)
{
	t_cmd	*new;

	if (!p->s[*i])
	{
		if (*i > 0 && p->s[*i - 1])
			ft_lstadd_back(&p->args, ft_lstnew(ft_substr(p->s, 0, *i)));
		new = new_cmd(FLG_EOL, &p->args);
		ft_lstadd_back(&singleton()->lst, ft_lstnew(new));
		return (TRUE);
	}
	return (FALSE);
}
