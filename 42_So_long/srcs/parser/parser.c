/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 21:24:09 by kaye              #+#    #+#             */
/*   Updated: 2021/07/05 19:57:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(void)
{
	int	i;

	i = 0;
	ft_putstr(B_CLRSCREEN);
	ft_putstr(B_GREEN"-- Map --\n\n"NONE);
	while (singleton()->map && singleton()->map[i])
		ft_printf("[%s]\n", singleton()->map[i++]);
	ft_putstr(B_GREEN"\n--Total collectible --\n\n"NONE);
	ft_printf("Collectible : [%d]\n", singleton()->collectible);
	ft_putstr(B_GREEN"\n-- Player move --\n\n"NONE);
}

void	init_value(t_parser p)
{
	int			i;
	int			j;

	i = 0;
	while (singleton()->map[i])
	{
		j = 0;
		while (singleton()->map[i][j])
		{
			if (singleton()->map[i][j] == 'C')
				++singleton()->collectible;
			if (singleton()->map[i][j] == 'P')
			{
				singleton()->player.x = j;
				singleton()->player.y = i;
				singleton()->map[i][j] = '0';
			}
			++j;
		}
		++i;
	}
	singleton()->len_frame_x = p.len;
	singleton()->len_frame_y = p.i;
}

void	parsing(char *path)
{
	t_parser	p;
	t_parser	map;

	p = parsing_check(path);
	singleton()->map = ft_calloc(sizeof(char *), (p.i + 1));
	if (!singleton()->map)
		__exit__(E_MALLOC, NULL, NOTHING, FAILURE);
	ft_bzero(&map, sizeof(t_parser));
	map.fd = __open__(path, O_RDONLY);
	map.ret = 1;
	while (map.ret)
	{
		map.ret = get_next_line(map.fd, &map.line);
		singleton()->map[map.i++] = ft_strdup(map.line);
		free(map.line);
	}
	close(map.fd);
	init_value(p);
	print_map();
}
