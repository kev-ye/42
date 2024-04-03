/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:14:36 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:38:44 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	*ft_mcat(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	return (new);
}

static char	*ft_realloc_str(char *str, char **line, int *check)
{
	char			*new;
	unsigned int	i;

	new = NULL;
	if (str)
	{
		i = 0;
		while (str[i] && str[i] != '\n')
			++i;
		if (str[i] == '\n')
		{
			*check = 1;
			new = ft_strdup(str + i + 1);
		}
		else if (str[i])
			new = ft_strdup(str + i);
		*line = ft_substr(str, 0, i);
		free(str);
	}
	return (new);
}

static char	*ft_read_line(int fd, char *str, char **line, int *check)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	int		r;

	r = 1;
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buffer[r] = '\0';
		tmp = str;
		str = ft_mcat(str, buffer);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (ft_realloc_str(str, line, check));
}

int	get_next_line(int fd, char **line)
{
	static char	*strs[FD_LIMIT];
	int			check;

	if (fd < 0 || fd >= FD_LIMIT || read(fd, strs[fd], 0)
		|| BUFFER_SIZE <= 0 || !line)
		return (-1);
	check = 0;
	if (strs[fd] && ft_strchr(strs[fd], '\n'))
	{
		strs[fd] = ft_realloc_str(strs[fd], line, &check);
		return (check);
	}
	if (!strs[fd])
	{
		strs[fd] = ft_strdup("");
		if (!strs[fd])
			return (-1);
	}
	strs[fd] = ft_read_line(fd, strs[fd], line, &check);
	return (check);
}
