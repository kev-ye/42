/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:33:10 by kaye              #+#    #+#             */
/*   Updated: 2021/02/19 16:51:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		**get_map_line(int *fd, char *line, char **map, int x_max)
{
	t_var var;

	var.r = 1;
	var.i = 0;
	while (var.r > 0)
	{
		var.j = 0;
		var.r = get_next_line(*fd, &line);
		if (map_line(line))
		{
			if (!(map[var.i] = ft_strdup(line)))
				return (NULL);
			var.len = ft_strlen(map[var.i]);
			while (var.len + var.j < x_max)
			{
				if (!(map[var.i] = ft_strjoin_gnl(map[var.i], " ")))
					return (NULL);
				var.j++;
			}
			var.i++;
		}
		free(line);
	}
	return (map);
}

char			**get_map2(const char *path, int fd, int y_max, int x_max)
{
	char	*line;
	char	**map;

	if (!(map = malloc(sizeof(char *) * (y_max))))
		return (NULL);
	if ((fd = open(path, O_RDWR | O_NOFOLLOW)) == -1)
		return (NULL);
	line = NULL;
	if (!(map = get_map_line(&fd, line, map, x_max)))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}
