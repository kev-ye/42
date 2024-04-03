/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configParsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:58:30 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:33:15 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_path_parsing(void)
{
	t_cub3d const	*ptr = sglt();
	int				fd;
	int				i;

	i = 0;
	while (i < PATHMAX)
	{
		fd = open(ptr->map_info.path[i++], O_RDWR);
		if (SYSCALL_ERROR == fd)
			exit_clean(E_PATH, __FILE__, __LINE__);
		close(fd);
	}
}

static void	_get_config(char const *path)
{
	t_cub3d	*ptr;
	t_list	*tmp;
	t_io	io_stream;

	ft_bzero(&io_stream, sizeof(io_stream));
	io_stream.fd = open(path, O_RDONLY);
	if (SYSCALL_ERROR == io_stream.fd)
		exit_clean(E_SYS, __FILE__, __LINE__);
	io_stream.ret = 1;
	tmp = NULL;
	while (io_stream.ret > 0)
	{
		io_stream.ret = gnl(&(io_stream.fd), &(io_stream.line), NULL);
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(io_stream.line)));
		free_clean((void **)&(io_stream.line));
	}
	close(io_stream.fd);
	ptr = sglt();
	ptr->config = lst2tab(tmp);
	ft_lstclear(&tmp, NULL);
}

static void	_config_empty(void)
{
	int	i;

	i = 0;
	while (NULL != sglt()->config && NULL != sglt()->config[i])
	{
		if ('\0' != sglt()->config[i++])
			break ;
	}
	if (NULL == sglt()->config[i])
		exit_clean(E_EMPTY, __FILE__, __LINE__);
}

static void	_filename_check(char const *path)
{
	int		i;
	size_t	len;

	len = ft_strlen(path) - 1;
	i = len;
	while (-1 != i)
		if ('.' == path[i--])
			break ;
	if (i == -1 || 4 != ft_strlen(path + i + 1)
		|| 0 != ft_strcmp(".cub", path + i + 1))
		exit_clean(USAGE, __FILE__, __LINE__);
}

void	config_parsing(char const *path)
{
	int	index;

	_filename_check(path);
	_get_config(path);
	_config_empty();
	index = info_config_parsing();
	_path_parsing();
	map_config_parsing(index);
	map_parsing();
}
