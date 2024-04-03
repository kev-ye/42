/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:37:11 by kaye              #+#    #+#             */
/*   Updated: 2020/08/20 11:01:30 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
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

int		main(int ac, char **av)
{
	char	buffer[BUF_MAX + 1];
	int		fd;
	int		ret;

	fd = 0;
	if (ac < 2)
		ft_putstr_fd(STDERR_FILENO, "File name missing.\n");
	else if (ac > 2)
		ft_putstr_fd(STDERR_FILENO, "Too many arguments.\n");
	else
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(STDERR_FILENO, "Cannot read file.\n");
			return (0);
		}
		while ((ret = read(fd, buffer, BUF_MAX)))
		{
			buffer[ret] = '\0';
			write(STDOUT_FILENO, buffer, ret);
		}
	}
	close(fd);
	return (0);
}
