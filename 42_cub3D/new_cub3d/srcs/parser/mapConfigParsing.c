/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapConfigParsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:58:28 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:25:23 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_idx
{
	int	i;
	int	j;
	int	k;
	int	player;
}	t_idx;

static char const	g_map[] = {
	'0',
	'1',
	'N',
	'S',
	'E',
	'W',
	' ',
	'\0'
};

static char const	g_ply[] = {
	'N',
	'S',
	'E',
	'W',
	'\0'
};

static void	_get_map(int const index)
{
	t_cub3d	*ptr;
	t_list	*tmp;
	int		i;

	i = index;
	while (NULL != sglt()->config[i] && 0 == sglt()->config[i][0])
		++i;
	tmp = NULL;
	while (NULL != sglt()->config[i])
	{
		if (NULL == sglt()->config[i + 1] && sglt()->config[i][0] == '\0')
			break ;
		ft_lstadd_back(&tmp, ft_lstnew((char *)sglt()->config[i++]));
	}
	ptr = sglt();
	ptr->map_info.map = lst2tab(tmp);
	ft_lstclear(&tmp, NULL);
}

static void	_map_line_check(char *line)
{
	int	i;
	int	j;

	if (0 == line[0])
		exit_clean(E_MAP, __FILE__, __LINE__);
	i = 0;
	while ('\0' != line[i])
	{
		j = 0;
		while ('\0' != g_map[j])
		{
			if (line[i] == g_map[j])
				break ;
			++j;
		}
		if (0 == g_map[j])
			exit_clean(E_MAP, __FILE__, __LINE__);
		++i;
	}
}

static void	_get_player_pos(
	int const pos_x,
	int const pos_y,
	char const direction
)
{
	t_cub3d	*ptr;

	ptr = sglt();
	ptr->player.pos_x = (double)pos_x;
	ptr->player.pos_y = (double)pos_y;
	ptr->player.direction = direction;
}

static void	_one_player(void)
{
	t_idx	idx;

	ft_bzero(&idx, sizeof(t_idx));
	while (NULL != sglt()->map_info.map && NULL != sglt()->map_info.map[idx.i])
	{
		idx.j = 0;
		while ('\0' != sglt()->map_info.map[idx.i][idx.j])
		{
			idx.k = 0;
			while ('\0' != g_ply[idx.k])
			{
				if (sglt()->map_info.map[idx.i][idx.j] == g_ply[idx.k])
				{
					_get_player_pos(idx.i, idx.j, g_ply[idx.k]);
					++idx.player;
					break ;
				}
				++idx.k;
			}
			++idx.j;
		}
		++idx.i;
	}
	if (1 != idx.player)
		exit_clean(E_PLAYER, __FILE__, __LINE__);
}

void	map_config_parsing(int const index)
{
	int	i;

	_get_map(index);
	i = 0;
	while (NULL != sglt()->map_info.map && NULL != sglt()->map_info.map[i])
		_map_line_check(sglt()->map_info.map[i++]);
	_one_player();
}
