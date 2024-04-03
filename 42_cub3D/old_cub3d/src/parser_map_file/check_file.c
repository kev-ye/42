/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:19:17 by kaye              #+#    #+#             */
/*   Updated: 2021/02/26 11:14:14 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		parser_map(const char *path, t_desc_info *desc_info, t_win *win)
{
	char	**map;
	int		len_max_y;
	int		len_max_x;

	if (!(map = get_map(path, &len_max_y, &len_max_x)))
		return (0);
	(*desc_info).map_y = len_max_y;
	(*desc_info).map_x = len_max_x;
	(*desc_info).map = get_player_place(map, &(*desc_info).player_x,
											&(*desc_info).player_y, desc_info);
	if ((*desc_info).map == NULL)
	{
		free_desc_info(desc_info);
		msg_error(win, "File -> Player error\n");
	}
	if (!check_map(map, len_max_y))
		return (0);
	return (1);
}

static int		check_file_id(
		t_win *win,
		int *fd,
		char *line,
		t_desc_info *desc_info)
{
	int r;

	r = 1;
	while (r > 0)
	{
		r = get_next_line(*fd, &line);
		if (!line)
			return (r);
		if (!check_file_line(line, &desc_info->desc, desc_info))
		{
			free(line);
			free_desc_info(desc_info);
			close(*fd);
			msg_error(win, "File -> ID error\n");
		}
		free(line);
		if (check_map_ready(desc_info->desc))
			return (r);
	}
	return (r);
}

static int		check_is_map(
		t_win *win, int *fd,
		char *line,
		t_desc_info *desc_info)
{
	int r;

	r = 1;
	while (r > 0)
	{
		r = get_next_line(*fd, &line);
		if (!line)
			return (r);
		if (!check_no_map(line, &desc_info->desc))
		{
			free(line);
			free_desc_info(desc_info);
			close(*fd);
			msg_error(win, "File -> ID error\n");
		}
		free(line);
		if (desc_info->desc.map == 1)
			return (r);
	}
	return (r);
}

static void		check_map_get_ready(
		t_win *win,
		int *fd,
		char *line,
		t_desc_info *desc_info)
{
	int r;

	r = 1;
	while (r > 0)
	{
		r = get_next_line(*fd, &line);
		if (!line)
			return ;
		if (!check_map_norm(line))
		{
			free(line);
			free_desc_info(desc_info);
			close(*fd);
			msg_error(win, "File -> Map error\n");
		}
		free(line);
	}
}

t_desc_info		*check_file(t_win *win, const char *path)
{
	char			*line;
	int				fd;
	t_desc_info		*desc_info;

	if (!(check_file_name(path)))
		msg_error(win, "File -> File name error\n");
	if ((fd = open(path, O_RDWR | O_NOFOLLOW)) == -1)
		msg_error(win, "File -> File no exist / no correct\n");
	if (!(desc_info = init_desc_info()))
		return (NULL);
	line = NULL;
	if (check_file_id(win, &fd, line, desc_info) > 0)
		if (check_is_map(win, &fd, line, desc_info) > 0)
			check_map_get_ready(win, &fd, line, desc_info);
	close(fd);
	if (!check_path(desc_info))
	{
		free_desc_info(desc_info);
		msg_error(win, "Path -> Path no exist / no content\n");
	}
	if (!parser_map(path, desc_info, win))
		msg_error(win, "Map -> Map error\n");
	return (desc_info);
}
