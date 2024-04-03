/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 17:21:27 by kaye              #+#    #+#             */
/*   Updated: 2021/02/24 14:09:14 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_side(
		t_ray_cast *ray,
		t_win *win,
		t_line *line,
		double wall_x)
{
	int		tex_x;
	t_img	*img;

	img = win->texture[3];
	if (ray->side == 1)
		img = win->texture[2];
	if (ray->side == 2)
		img = win->texture[0];
	if (ray->side == 3)
		img = win->texture[1];
	tex_x = (int)(wall_x * (double)img->width);
	if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
		tex_x = img->width - tex_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
		tex_x = img->width - tex_x - 1;
	line->draw_start = ray->draw_start;
	line->draw_end = ray->draw_end;
	line->tex_x = tex_x;
	draw_vertical_tex(line, win, img, ray);
}

void	draw_ceiling_floor(
		t_win *win,
		t_line *line,
		t_ray_cast *ray)
{
	line->draw_start = 0;
	line->draw_end = ray->draw_start;
	draw_vertical_color(line, win, win->desc_info->color_c);
	line->draw_start = ray->draw_end;
	line->draw_end = win->height;
	draw_vertical_color(line, win, win->desc_info->color_f);
}

void	mapping(
		t_ray_cast *ray,
		t_win *win)
{
	t_line	*line;
	double	wall_x;

	if (!(line = malloc(sizeof(t_line))))
		return ;
	ft_bzero(line, sizeof(t_line));
	line->line_x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wall_x = win->camera->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = win->camera->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (win->desc_info->map[ray->map_y][ray->map_x] == '1')
		draw_side(ray, win, line, wall_x);
	draw_ceiling_floor(win, line, ray);
	free(line);
}
