/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:50:52 by kaye              #+#    #+#             */
/*   Updated: 2020/08/23 19:51:45 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"

int		ft_open_valid(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int		ft_open_count(char *path)
{
	char	buffer[4092];
	int		fd;
	int		ret;
	int		count;

	ret = 0;
	count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while ((ret = read(fd, buffer, 4092)) > 0)
		count = count + ret;
	close(fd);
	return (count);
}

char	*ft_open_malloc(char *path)
{
	char	*stock_str;
	int		fd;
	int		count;

	count = ft_open_count(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	if (!(stock_str = (char*)malloc(sizeof(char) * count + 1)))
		return (NULL);
	read(fd, stock_str, count);
	stock_str[count] = '\0';
	close(fd);
	return (stock_str);
}
