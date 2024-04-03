/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:10:41 by kaye              #+#    #+#             */
/*   Updated: 2021/03/09 19:35:09 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

static char	*get_line(char *s)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		++i;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

static char	*next_line(char *s)
{
	char	*str;
	char	*tmp;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		++i;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s) - i + 1));
	if (!tmp)
		return (NULL);
	++i;
	str = tmp;
	while (s[i])
		*tmp++ = s[i++];
	*tmp = '\0';
	free(s);
	return (str);
}

static t_set	*current_set(t_set **set, int fd, t_set *tmp)
{
	if (!*set)
	{
		*set = ft_lstnew_gnl();
		if (!*set)
			return (NULL);
	}
	tmp = *set;
	if ((*set)->fd && (*set)->fd != fd)
	{
		while (tmp)
		{
			if (tmp->fd == fd)
				break ;
			tmp = tmp->next;
		}
	}
	else
		(*set)->fd = fd;
	if (!tmp)
	{
		tmp = ft_lstnew_gnl();
		ft_lstadd_front_gnl(&(*set), tmp);
		tmp->fd = fd;
	}
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	static t_set	*set;
	t_v3			var;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	var.ret = 1;
	var.tmp = current_set(&set, fd, var.tmp);
	while (!is_newline(var.tmp->str) && var.ret != 0)
	{
		var.ret = read(var.tmp->fd, var.buff, BUFFER_SIZE);
		if (var.ret < 0)
			return (-1);
		var.buff[var.ret] = '\0';
		var.tmp->str = ft_strjoin_gnl(var.tmp->str, var.buff);
	}
	*line = get_line(var.tmp->str);
	var.tmp->str = next_line(var.tmp->str);
	if (!var.tmp->str)
		ft_list_remove_gnl(&set);
	if (var.ret)
		return (1);
	return (0);
}
