/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_drawing_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:37:31 by kaye              #+#    #+#             */
/*   Updated: 2021/02/25 14:26:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		drawing(t_win *win, t_sp_cast *sp_cast, int i)
{
	if (win->desc_info->map[sp_cast->sprite[i].y]
			[sp_cast->sprite[i].x] == '2')
	{
		sp_cast->tex_x = (int)((sp_cast->stripe
						- (-sp_cast->sprite_width / 2
						+ sp_cast->sprite_screen_x))
						* win->sprite[0]->width / sp_cast->sprite_width);
	}
	if (win->desc_info->map[sp_cast->sprite[i].y]
			[sp_cast->sprite[i].x] == '3')
	{
		sp_cast->tex_x = (int)((sp_cast->stripe
						- (-sp_cast->sprite_width / 2
						+ sp_cast->sprite_screen_x))
						* win->sprite[2]->width / sp_cast->sprite_width);
	}
	if (win->desc_info->map[sp_cast->sprite[i].y]
			[sp_cast->sprite[i].x] == '4')
	{
		sp_cast->tex_x = (int)((sp_cast->stripe
						- (-sp_cast->sprite_width / 2
						+ sp_cast->sprite_screen_x))
						* win->sprite[1]->width / sp_cast->sprite_width);
	}
}

static void		drawing2(t_win *win, t_sp_cast *sp_cast, int i)
{
	pixel_put_sprite(win, sp_cast, i);
	if (win->desc_info->map[sp_cast->sprite[i].y]
			[sp_cast->sprite[i].x] == '2')
		if ((sp_cast->color & 0x00FFFFFF) != 0)
			paint_pixel(win, sp_cast, i);
	if (win->desc_info->map[sp_cast->sprite[i].y]
			[sp_cast->sprite[i].x] == '3')
		if ((sp_cast->color & 0x00FCFCFC) != 0x00FCFCFC)
			paint_pixel(win, sp_cast, i);
	if (win->desc_info->map[sp_cast->sprite[i].y]
			[sp_cast->sprite[i].x] == '4')
		if ((sp_cast->color & 0x000000FF) != 0x000000FF)
			paint_pixel(win, sp_cast, i);
}

void			sprite_drawing(
		t_win *win,
		t_sp_cast *sp_cast,
		t_ray_cast *ray,
		int i)
{
	while (sp_cast->stripe < sp_cast->draw_end_x)
	{
		drawing(win, sp_cast, i);
		if (sp_cast->transform_y > 0 && sp_cast->stripe > 0
				&& sp_cast->stripe < win->width
				&& sp_cast->transform_y < ray->zbuffer[sp_cast->stripe])
		{
			sp_cast->y = sp_cast->draw_start_y;
			while (sp_cast->y < sp_cast->draw_end_y)
			{
				drawing2(win, sp_cast, i);
				++sp_cast->y;
			}
		}
		++sp_cast->stripe;
	}
}
