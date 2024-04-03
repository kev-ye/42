/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:09:29 by kaye              #+#    #+#             */
/*   Updated: 2020/08/24 18:12:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*stock_file(int fd, int *size)
{
	char	buf[BUF_MAX];
	char	*stock;
	char	*stock_tmp;
	int		ret;

	if (!(stock = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	*stock = '\0';
	*size = 0;
	while ((ret = read(fd, buf, BUF_MAX)) > 0)
	{
		if (!(stock_tmp = (char*)malloc(sizeof(char) * (*size + ret))))
			break ;
		stock_tmp = ft_strncpy(stock_tmp, stock, *size);
		free(stock);
		ft_strncpy(stock_tmp + *size, buf, ret);
		stock = stock_tmp;
		*size = *size + ret;
		stock[*size] = '\0';
	}
	if (ret != 0)
		free(stock);
	return ((ret == 0) ? stock : NULL);
}

int		ft_tail(char *path, int condition, int count, int print_path)
{
	char	*stock;
	int		fd;
	int		size;

	fd = (path) ? open(path, O_RDONLY) : STDIN_FILENO;
	if (fd < 0)
		return (-1);
	stock = stock_file(fd, &size);
	if (fd != STDIN_FILENO)
		close(fd);
	if (stock == NULL)
		return (-1);
	if (print_path != 0)
	{
		if (count != 0)
			write(STDOUT_FILENO, "\n", 1);
		print_name_path(path);
	}
	if (condition > size)
		condition = size;
	ft_putstr_fd(STDOUT_FILENO, stock + size - condition);
	free(stock);
	return (0);
}

int		main(int ac, char **av)
{
	char	*origin;
	int		condition_av;
	int		condition_abs;
	int		count;
	int		i;

	if (ac < 3 || ft_strcmp(av[1], "-c"))
		return (0);
	origin = basename(av[0]);
	condition_av = ft_atoi(av[2]);
	condition_abs = (condition_av < 0) ? -condition_av : condition_av;
	if (ac < 4 && ft_tail(NULL, condition_abs, 0, 0) < 0)
		ft_error(origin, NULL, strerror(errno));
	count = 0;
	i = 3;
	while (i < ac)
	{
		if (ft_tail(av[i], condition_abs, count, ac > 4) < 0)
			ft_error(origin, av[i], strerror(errno));
		else
			count++;
		i++;
	}
	return (0);
}
