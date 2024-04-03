/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 17:20:32 by kaye              #+#    #+#             */
/*   Updated: 2021/02/18 12:03:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_w(t_win *win)
{
	if (win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x + win->camera->dir_x
				* win->camera->speed * 2)] == '0' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x + win->camera->dir_x
				* win->camera->speed * 2)] == '4' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x + win->camera->dir_x
				* win->camera->speed * 2)] == '3')
		win->camera->pos_x += win->camera->dir_x * win->camera->speed;
	if (win->desc_info->map[(int)(win->camera->pos_y + win->camera->dir_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '0' ||
			win->desc_info->map[(int)(win->camera->pos_y + win->camera->dir_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '4' ||
			win->desc_info->map[(int)(win->camera->pos_y + win->camera->dir_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '3')
		win->camera->pos_y += win->camera->dir_y * win->camera->speed;
}

void	move_s(t_win *win)
{
	if (win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x - win->camera->dir_x
				* win->camera->speed * 2)] == '0' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x - win->camera->dir_x
				* win->camera->speed * 2)] == '4' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x - win->camera->dir_x
				* win->camera->speed * 2)] == '3')
		win->camera->pos_x -= win->camera->dir_x * win->camera->speed;
	if (win->desc_info->map[(int)(win->camera->pos_y - win->camera->dir_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '0' ||
			win->desc_info->map[(int)(win->camera->pos_y - win->camera->dir_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '4' ||
			win->desc_info->map[(int)(win->camera->pos_y - win->camera->dir_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '3')
		win->camera->pos_y -= win->camera->dir_y * win->camera->speed;
}

void	move_a(t_win *win)
{
	if (win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x - win->camera->plane_x
				* win->camera->speed * 2)] == '0' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x - win->camera->plane_x
				* win->camera->speed * 2)] == '4' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x - win->camera->plane_x
				* win->camera->speed * 2)] == '3')
		win->camera->pos_x -= win->camera->plane_x * win->camera->speed;
	if (win->desc_info->map[(int)(win->camera->pos_y - win->camera->plane_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '0' ||
			win->desc_info->map[(int)(win->camera->pos_y - win->camera->plane_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '4' ||
			win->desc_info->map[(int)(win->camera->pos_y - win->camera->plane_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '3')
		win->camera->pos_y -= win->camera->plane_y * win->camera->speed;
}

void	move_d(t_win *win)
{
	if (win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x + win->camera->plane_x
				* win->camera->speed * 2)] == '0' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x + win->camera->plane_x
				* win->camera->speed * 2)] == '4' ||
			win->desc_info->map[(int)win->camera->pos_y]
			[(int)(win->camera->pos_x + win->camera->plane_x
				* win->camera->speed * 2)] == '3')
		win->camera->pos_x += win->camera->plane_x * win->camera->speed;
	if (win->desc_info->map[(int)(win->camera->pos_y + win->camera->plane_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '0' ||
			win->desc_info->map[(int)(win->camera->pos_y + win->camera->plane_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '4' ||
			win->desc_info->map[(int)(win->camera->pos_y + win->camera->plane_y
				* win->camera->speed * 2)][(int)win->camera->pos_x] == '3')
		win->camera->pos_y += win->camera->plane_y * win->camera->speed;
}
