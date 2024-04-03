/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:30:15 by kaye              #+#    #+#             */
/*   Updated: 2020/08/27 14:58:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libgen.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include "ft.h"

#define BUF_MAX 4092

int		ft_strlen(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void	ft_error(char *orgin, char *path, char *err)
{
	ft_putstr_fd(STDERR_FILENO, orgin);
	ft_putstr_fd(STDERR_FILENO, ": ");
	ft_putstr_fd(STDERR_FILENO, path);
	ft_putstr_fd(STDERR_FILENO, ": ");
	ft_putstr_fd(STDERR_FILENO, err);
	write(STDERR_FILENO, "\n", 1);
}

int		ft_cat(char *path)
{
	char	buf[BUF_MAX];
	int		fd;
	int		ret;

	fd = 0;
	if (path == NULL)
		fd = STDIN_FILENO;
	else
		fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((ret = read(fd, buf, BUF_MAX)) > 0)
		write(STDOUT_FILENO, buf, ret);
	if (fd != STDIN_FILENO)
		close(fd);
	if (ret == 0)
		return (0);
	return (-1);
}

int		main(int ac, char **av)
{
	char	*origin;
	int		i;

	origin = basename(av[0]);
	i = 1;
	if (ac < 2 && ft_cat(NULL) < 0)
		ft_error(origin, NULL, strerror(errno));
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-") == 0)
			av[i] = NULL;
		if (ft_cat(av[i]) < 0)
			ft_error(origin, av[i], strerror(errno));
		i++;
	}
	return (0);
}
