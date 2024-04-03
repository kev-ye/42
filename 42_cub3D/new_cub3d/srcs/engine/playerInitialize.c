/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerInitialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:57:40 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 23:32:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DIR_INFOMAX	4

typedef struct s_dir_info
{
	char	id;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_dir_info;

static t_dir_info const	g_dir[] = {
{'N', 0.0, -1.0, 0.66, 0.0},
{'S', 0.0, 1.0, -0.66, 0.0},
{'W', -1.0, 0.0, 0.0, -0.66},
{'E', 1.0, 0.0, 0.0, 0.66},
};

static void	_set_player_dir(t_player *player)
{
	int	i;

	i = 0;
	while (i < DIR_INFOMAX)
	{
		if (player->direction == g_dir[i].id)
		{
			player->dir_x = g_dir[i].dir_x;
			player->dir_y = g_dir[i].dir_y;
			player->plane_x = g_dir[i].plane_x;
			player->plane_y = g_dir[i].plane_y;
		}
		++i;
	}
}

void	player_initialize(void)
{
	t_player	*player;

	player = &sglt()->player;
	player->pos_x += 0.5;
	player->pos_y += 0.5;
	_set_player_dir(player);
	player->rot_speed = 0.10;
	player->speed = 0.10;
	player->cam_height = 1.0;
}
