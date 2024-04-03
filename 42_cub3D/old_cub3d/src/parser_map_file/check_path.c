/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:17:38 by kaye              #+#    #+#             */
/*   Updated: 2021/03/01 19:53:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_path_name(char *path, int *fd)
{
	char *s;

	if (!path)
		return (0);
	s = ft_strrchr(path, '.');
	if (ft_strcmp(s, ".xpm") != 0)
		return (0);
	if ((*fd = open(path, O_RDONLY)) == -1)
		return (0);
	close(*fd);
	return (1);
}

int			check_path(t_desc_info *desc_info)
{
	int fd;

	if (!desc_info->path_no || !(check_path_name(desc_info->path_no, &fd)))
		return (0);
	if (!desc_info->path_so || !(check_path_name(desc_info->path_so, &fd)))
		return (0);
	if (!desc_info->path_we || !(check_path_name(desc_info->path_we, &fd)))
		return (0);
	if (!desc_info->path_ea || !(check_path_name(desc_info->path_ea, &fd)))
		return (0);
	if (!desc_info->path_s || !(check_path_name(desc_info->path_s, &fd)))
		return (0);
	return (1);
}
