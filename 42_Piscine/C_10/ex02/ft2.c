/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:06:20 by kaye              #+#    #+#             */
/*   Updated: 2020/08/27 14:40:50 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

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

void	print_name_path(char *path)
{
	ft_putstr_fd(STDOUT_FILENO, "==> ");
	ft_putstr_fd(STDOUT_FILENO, path);
	ft_putstr_fd(STDOUT_FILENO, " <==\n");
}
