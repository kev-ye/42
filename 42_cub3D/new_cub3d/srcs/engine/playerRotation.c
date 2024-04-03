/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerRotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:17:04 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 23:39:38 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_left(void)
{
	t_cub3d		*ptr;
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	ptr = sglt();
	player = &ptr->player;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-player->rot_speed)
		- player->dir_y * sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed)
		+ player->dir_y * cos(-player->rot_speed);
	player->plane_x = player->plane_x * cos(-player->rot_speed)
		- player->plane_y * sin(-player->rot_speed);
	player->plane_y = old_plane_x * sin(-player->rot_speed)
		+ player->plane_y * cos(-player->rot_speed);
}

void	rot_right(void)
{
	t_cub3d		*ptr;
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	ptr = sglt();
	player = &ptr->player;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(player->rot_speed)
		- player->dir_y * sin(player->rot_speed);
	player->dir_y = old_dir_x * sin(player->rot_speed)
		+ player->dir_y * cos(player->rot_speed);
	player->plane_x = player->plane_x * cos(player->rot_speed)
		- player->plane_y * sin(player->rot_speed);
	player->plane_y = old_plane_x * sin(player->rot_speed)
		+ player->plane_y * cos(player->rot_speed);
}
