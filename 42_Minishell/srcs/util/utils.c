/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:15:55 by besellem          #+#    #+#             */
/*   Updated: 2021/06/23 15:14:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_openable(char *path, int flag)
{
	int	fd;

	fd = open(path, flag);
	if (-1 == fd)
		return (0);
	close(fd);
	return (1);
}

/*
** Clean characters from `charset' found in `s'
** /!\ it modifies `s'
**
** ex:
** ft_strclean(";bonjour >to<i", ";<>");
** => "bonjour toi"
*/
char	*ft_strnclean(char *s, const char *charset, size_t end)
{
	size_t	i;
	size_t	j;

	if (!s || !charset)
		return (s);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (i >= end || !ft_incharset(charset, s[i]))
			s[j++] = s[i];
		++i;
	}
	ft_bzero(s + j, ft_strlen(s + j));
	return (s);
}

void	*ft_error(char *message, char *file, int line)
{
	ft_dprintf(STDERR_FILENO, B_RED "%s:%d: " CLR_COLOR "%s\n",
		file, line, message);
	ft_free_exit(EXEC_FAILURE);
	return (NULL);
}

t_list	*search_env(char *tofind, t_list **env)
{
	t_list	*tmp;
	size_t	len_tofind;

	len_tofind = 0;
	while (tofind[len_tofind] && tofind[len_tofind] != '=')
		++len_tofind;
	tmp = *env;
	while (tmp)
	{
		if ((char *)tmp->content
			&& 0 == ft_strncmp((char *)tmp->content, tofind, len_tofind)
			&& (((char *)(tmp->content))[len_tofind] == '='
			|| ((char *)(tmp->content))[len_tofind] == '\0'))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_getenv(const char *name)
{
	t_list	*tmp;
	int		idx;
	char	*ptr;

	if (!name)
		return (NULL);
	tmp = singleton()->env;
	while (tmp)
	{
		ptr = ft_strchr(tmp->content, '=');
		if (ptr)
		{
			idx = ft_stridx(tmp->content, "=");
			if (idx != NOT_FOUND && 0 == ft_strncmp(name, tmp->content, idx))
				return (ft_strdup(ptr + 1));
		}
		else
		{
			if (0 == ft_strcmp(name, tmp->content))
				return (ft_strdup(""));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
