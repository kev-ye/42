/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:51:29 by kaye              #+#    #+#             */
/*   Updated: 2021/02/25 12:53:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sp_cast	*get_sprite_pos(t_win *win)
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
			if (win->desc_info->map[y][x] == '2')
			{
				sp_cast->sprite[count].x = x;
				sp_cast->sprite[count].y = y;
				++count;
			}
		}
	}
	return (sp_cast);
}

void		pixel_put_sprite(t_win *win, t_sp_cast *sp_cast)
{
	sp_cast->tex_y = ((sp_cast->y - win->height / 2
						+ sp_cast->sprite_height / 2)
						* win->sprite->height) / sp_cast->sprite_height;
	ft_memcpy(&sp_cast->color, win->sprite->addr + sp_cast->tex_y
			* win->sprite->line_len + sp_cast->tex_x * win->sprite->bpp / 8,
			sizeof(unsigned int));
}

void		paint_pixel(t_win *win, t_sp_cast *sp_cast)
{
	ft_memcpy(win->img->addr + sp_cast->y * win->img->line_len
			+ sp_cast->stripe * win->img->bpp / 8, win->sprite->addr
			+ sp_cast->tex_y * win->sprite->line_len + sp_cast->tex_x
			* win->sprite->bpp / 8, sizeof(unsigned int));
}
