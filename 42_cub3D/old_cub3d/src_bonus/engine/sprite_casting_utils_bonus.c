/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:51:29 by kaye              #+#    #+#             */
/*   Updated: 2021/02/25 14:23:38 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_sp_cast		*get_sprite_pos(t_win *win)
{
	t_sp_cast	*sp_cast;
	int			count;
	int			x;
	int			y;

	if (!(sp_cast = sprite_cast_init(win)))
		return (NULL);
	count = 0;
	y = -1;
	while (++y < win->desc_info->map_y)
	{
		x = -1;
		while (++x < win->desc_info->map_x)
		{
			if (win->desc_info->map[y][x] == '2' ||
					win->desc_info->map[y][x] == '3' ||
					win->desc_info->map[y][x] == '4')
			{
				sp_cast->sprite[count].x = x;
				sp_cast->sprite[count].y = y;
				++count;
			}
		}
	}
	return (sp_cast);
}

static void		pixel_put_sprite2(t_win *win, t_sp_cast *sp_cast, int i)
{
	if (win->desc_info->map[sp_cast->sprite[i].y][sp_cast->sprite[i].x] == '4')
	{
		sp_cast->tex_y = ((sp_cast->y - win->height / 2
				* win->camera->cam_height + sp_cast->sprite_height / 2)
				* win->sprite[1]->height) / sp_cast->sprite_height;
		ft_memcpy(&sp_cast->color, win->sprite[1]->addr + sp_cast->tex_y
		* win->sprite[1]->line_len + sp_cast->tex_x * win->sprite[1]->bpp / 8,
				sizeof(unsigned int));
	}
}

void			pixel_put_sprite(t_win *win, t_sp_cast *sp_cast, int i)
{
	if (win->desc_info->map[sp_cast->sprite[i].y][sp_cast->sprite[i].x] == '2')
	{
		sp_cast->tex_y = ((sp_cast->y - win->height / 2
				* win->camera->cam_height + sp_cast->sprite_height / 2)
				* win->sprite[0]->height) / sp_cast->sprite_height;
		ft_memcpy(&sp_cast->color, win->sprite[0]->addr + sp_cast->tex_y
		* win->sprite[0]->line_len + sp_cast->tex_x * win->sprite[0]->bpp / 8,
				sizeof(unsigned int));
	}
	if (win->desc_info->map[sp_cast->sprite[i].y][sp_cast->sprite[i].x] == '3')
	{
		sp_cast->tex_y = ((sp_cast->y - win->height / 2
				* win->camera->cam_height + sp_cast->sprite_height / 2)
				* win->sprite[2]->height) / sp_cast->sprite_height;
		ft_memcpy(&sp_cast->color, win->sprite[2]->addr + sp_cast->tex_y
		* win->sprite[2]->line_len + sp_cast->tex_x * win->sprite[2]->bpp / 8,
				sizeof(unsigned int));
	}
	pixel_put_sprite2(win, sp_cast, i);
}

void			paint_pixel(t_win *win, t_sp_cast *sp_cast, int i)
{
	if (win->desc_info->map[sp_cast->sprite[i].y][sp_cast->sprite[i].x] == '2')
		ft_memcpy(win->img->addr + sp_cast->y * win->img->line_len
				+ sp_cast->stripe * win->img->bpp / 8, win->sprite[0]->addr
				+ sp_cast->tex_y * win->sprite[0]->line_len + sp_cast->tex_x
				* win->sprite[0]->bpp / 8, sizeof(unsigned int));
	if (win->desc_info->map[sp_cast->sprite[i].y][sp_cast->sprite[i].x] == '3')
		ft_memcpy(win->img->addr + sp_cast->y * win->img->line_len
				+ sp_cast->stripe * win->img->bpp / 8, win->sprite[2]->addr
				+ sp_cast->tex_y * win->sprite[2]->line_len + sp_cast->tex_x
				* win->sprite[2]->bpp / 8, sizeof(unsigned int));
	if (win->desc_info->map[sp_cast->sprite[i].y][sp_cast->sprite[i].x] == '4')
		ft_memcpy(win->img->addr + sp_cast->y * win->img->line_len
				+ sp_cast->stripe * win->img->bpp / 8, win->sprite[1]->addr
				+ sp_cast->tex_y * win->sprite[1]->line_len + sp_cast->tex_x
				* win->sprite[1]->bpp / 8, sizeof(unsigned int));
}
