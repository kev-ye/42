/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:22:41 by kaye              #+#    #+#             */
/*   Updated: 2021/02/16 14:36:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sort_sprite(t_win *win, t_sp_cast *sp_cast)
{
	double		sprite_dist[2];
	t_sprite	tmp;
	int			count;

	count = 0;
	while (count + 1 < sp_cast->sp_amount)
	{
		sprite_dist[0] = ((win->camera->pos_x - sp_cast->sprite[count].x)
				* (win->camera->pos_x - sp_cast->sprite[count].x)
				+ (win->camera->pos_y - sp_cast->sprite[count].y)
				* (win->camera->pos_y - sp_cast->sprite[count].y));
		sprite_dist[1] = ((win->camera->pos_x - sp_cast->sprite[count + 1].x)
				* (win->camera->pos_x - sp_cast->sprite[count + 1].x)
				+ (win->camera->pos_y - sp_cast->sprite[count + 1].y)
				* (win->camera->pos_y - sp_cast->sprite[count + 1].y));
		if (sprite_dist[0] < sprite_dist[1])
		{
			tmp = sp_cast->sprite[count];
			sp_cast->sprite[count] = sp_cast->sprite[count + 1];
			sp_cast->sprite[count + 1] = tmp;
			count = 0;
		}
		else
			++count;
	}
}

void	sprite_projection(t_win *win, t_sp_cast *sp_cast, int i)
{
	sp_cast->sprite_x = sp_cast->sprite[i].x - (win->camera->pos_x - 0.5);
	sp_cast->sprite_y = sp_cast->sprite[i].y - (win->camera->pos_y - 0.5);
	sp_cast->inv_det = 1.0 / (win->camera->plane_x * win->camera->dir_y
			- win->camera->dir_x * win->camera->plane_y);
	sp_cast->transform_x = sp_cast->inv_det * (win->camera->dir_y
			* sp_cast->sprite_x - win->camera->dir_x
			* sp_cast->sprite_y);
	sp_cast->transform_y = sp_cast->inv_det * (-win->camera->plane_y
			* sp_cast->sprite_x + win->camera->plane_x
			* sp_cast->sprite_y);
	sp_cast->sprite_screen_x = (int)((win->width / 2) *
			(1 + sp_cast->transform_x / sp_cast->transform_y));
}

void	sprite_draw(t_win *win, t_sp_cast *sp_cast, t_ray_cast *ray, int i)
{
	sp_cast->sprite_height = abs((int)(win->height / (sp_cast->transform_y)));
	sp_cast->draw_start_y = -sp_cast->sprite_height / 2
								+ win->height / 2 * win->camera->cam_height;
	if (sp_cast->draw_start_y < 0)
		sp_cast->draw_start_y = 0;
	sp_cast->draw_end_y = sp_cast->sprite_height / 2
								+ win->height / 2 * win->camera->cam_height;
	if (sp_cast->draw_end_y >= win->height)
		sp_cast->draw_end_y = win->height - 1;
	sp_cast->sprite_width = abs((int)(win->height / (sp_cast->transform_y)));
	sp_cast->draw_start_x = -sp_cast->sprite_width / 2
													+ sp_cast->sprite_screen_x;
	if (sp_cast->draw_start_x < 0)
		sp_cast->draw_start_x = 0;
	sp_cast->draw_end_x = sp_cast->sprite_width / 2 + sp_cast->sprite_screen_x;
	if (sp_cast->draw_end_x >= win->width)
		sp_cast->draw_end_x = win->width - 1;
	sp_cast->stripe = sp_cast->draw_start_x;
	sprite_drawing(win, sp_cast, ray, i);
}

int		sprite_casting(t_win *win, t_ray_cast *ray)
{
	t_sp_cast	*sp_cast;
	int			i;

	if (!(sp_cast = get_sprite_pos(win)))
		return (0);
	sort_sprite(win, sp_cast);
	i = 0;
	while (i < sp_cast->sp_amount)
	{
		sprite_projection(win, sp_cast, i);
		sprite_draw(win, sp_cast, ray, i);
		i++;
	}
	free(sp_cast->sprite);
	free(sp_cast);
	return (1);
}
