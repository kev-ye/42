/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:45:45 by kaye              #+#    #+#             */
/*   Updated: 2021/02/19 16:50:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				map_line(char *line)
{
	int i;

	i = 0;
	if (!line[0])
		return (0);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1'
				|| line[i] == '2' || line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
			++i;
		else
			return (0);
	}
	return (1);
}

static int		get_map_y_max(const char *path, int fd)
{
	char	*line;
	int		y_max;
	int		r;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	y_max = 0;
	r = 1;
	while (r > 0)
	{
		r = get_next_line(fd, &line);
		if (map_line(line))
			++y_max;
		free(line);
	}
	close(fd);
	return (y_max);
}

static int		get_map_x_max(const char *path, int fd)
{
	char	*line;
	int		x_max;
	int		r;
	int		i;

	if ((fd = open(path, O_RDWR | O_NOFOLLOW)) == -1)
		return (0);
	x_max = 0;
	r = 1;
	while (r > 0)
	{
		i = 0;
		r = get_next_line(fd, &line);
		while (line[i] && map_line(line))
			i++;
		if (x_max < i)
			x_max = i;
		free(line);
	}
	close(fd);
	return (x_max);
}

char			**get_map(const char *path, int *len_max_y, int *len_max_x)
{
	int		fd;
	char	**map;

	fd = 0;
	if (!(*len_max_y = get_map_y_max(path, fd)))
		return (NULL);
	if (!(*len_max_x = get_map_x_max(path, fd)))
		return (NULL);
	if (!(map = get_map2(path, fd, *len_max_y, *len_max_x)))
		return (NULL);
	return (map);
}
