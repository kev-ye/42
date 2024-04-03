/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:44:32 by kaye              #+#    #+#             */
/*   Updated: 2020/11/21 20:54:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int		is_newline(char *s)
{
	int i;

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

static char		*get_line(char *s)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		++i;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
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

static char		*next_line(char *s)
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
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(s) - i + 1))))
		return (NULL);
	++i;
	str = tmp;
	while (s[i])
		*tmp++ = s[i++];
	*tmp = '\0';
	free(s);
	return (str);
}

static t_set	*current_set(t_set **set, int fd)
{
	t_set *tmp;

	if (!*set)
		if (!(*set = ft_lstnew_gnl()))
			return (NULL);
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

int				get_next_line(int fd, char **line)
{
	static t_set	*set;
	t_set			*tmp;
	char			*buff;
	int				ret;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ret = 1;
	tmp = current_set(&set, fd);
	while (!is_newline(tmp->str) && ret != 0)
	{
		if ((ret = read(tmp->fd, buff, BUFFER_SIZE)) < 0)
			return (-1);
		buff[ret] = '\0';
		tmp->str = ft_strjoin_gnl(tmp->str, buff);
	}
	free(buff);
	*line = get_line(tmp->str);
	tmp->str = next_line(tmp->str);
	if (!tmp->str)
		ft_list_remove_gnl(&set);
	return ((ret) ? 1 : 0);
}
