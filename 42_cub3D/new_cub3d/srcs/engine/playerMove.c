/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:01:51 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 23:39:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_w(void)
{
	t_cub3d		*ptr;
	t_player	*ply;

	ptr = sglt();
	ply = &ptr->player;
	if (ptr->map_info.map[(int)ply->pos_y]
		[(int)(ply->pos_x + ply->dir_x * ply->speed * 2)] == '0')
		ply->pos_x += ply->dir_x * ply->speed;
	if (ptr->map_info.map[(int)(ply->pos_y + ply->dir_y * ply->speed * 2)]
		[(int)ply->pos_x] == '0')
		ply->pos_y += ply->dir_y * ply->speed;
}

void	move_s(void)
{
	t_cub3d		*ptr;
	t_player	*ply;

	ptr = sglt();
	ply = &ptr->player;
	if (ptr->map_info.map[(int)ply->pos_y]
		[(int)(ply->pos_x - ply->dir_x * ply->speed * 2)] == '0')
		ply->pos_x -= ply->dir_x * ply->speed;
	if (ptr->map_info.map[(int)(ply->pos_y - ply->dir_y * ply->speed * 2)]
		[(int)ply->pos_x] == '0')
		ply->pos_y -= ply->dir_y * ply->speed;
}

void	move_a(void)
{
	t_cub3d		*ptr;
	t_player	*ply;

	ptr = sglt();
	ply = &ptr->player;
	if (ptr->map_info.map[(int)ply->pos_y]
		[(int)(ply->pos_x - ply->plane_x * ply->speed * 2)] == '0')
		ply->pos_x -= ply->plane_x * ply->speed;
	if (ptr->map_info.map[(int)(ply->pos_y - ply->plane_y * ply->speed * 2)]
		[(int)ply->pos_x] == '0')
		ply->pos_y -= ply->plane_y * ply->speed;
}

void	move_d(void)
{
	t_cub3d		*ptr;
	t_player	*ply;

	ptr = sglt();
	ply = &ptr->player;
	if (ptr->map_info.map[(int)ply->pos_y]
		[(int)(ply->pos_x + ply->plane_x * ply->speed * 2)] == '0')
		ply->pos_x += ply->plane_x * ply->speed;
	if (ptr->map_info.map[(int)(ply->pos_y + ply->plane_y * ply->speed * 2)]
		[(int)ply->pos_x] == '0')
		ply->pos_y += ply->plane_y * ply->speed;
}
