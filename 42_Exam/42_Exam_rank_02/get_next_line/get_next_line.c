/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:08:56 by kaye              #+#    #+#             */
/*   Updated: 2021/03/10 17:13:43 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

static char *ft_join(char *s1, char *s2)
{
	size_t len;
	char *s;
	int i;

	if (!s1 && !s2)
		return (NULL);
	len = ((s1)? ft_strlen(s1) : 0) + ((s2)? ft_strlen(s2) : 0);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		*s++ = s1[i++];
	i = 0;
	while (s2 && s2[i])
		*s++ = s2[i++];
	*s = '\0';
	if (s1)
		free(s1);
	return (s - len);
}

static int ft_newline(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char *ft_getline(char *s)
{
	char *str;
	int i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char *ft_nextline(char *s)
{
	char *str;
	int i = 0;
	int j = 0;

	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (s[i])
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(s);
	return (str);
}

int				get_next_line(char **line)
{
	static char *s;
	int ret = 1;
	char buff[1024 + 1];

	if (!line)
		return (-1);
	while (!ft_newline(s) && ret != 0)
	{
		ret = read(0, buff, 1024);
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		s = ft_join(s, buff);
	}
	*line = ft_getline(s);
	s = ft_nextline(s);
	return ((ret) ? 1 : 0);
}