/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:15:23 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 23:31:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_draw_side(t_line *l, double wall_x, t_raycast *ray)
{
	t_img const	tex_view_by_player[TEXMAX] = {
		sglt()->tex_img[e_EA],
		sglt()->tex_img[e_WE],
		sglt()->tex_img[e_SO],
		sglt()->tex_img[e_NO]
	};
	int			tex_x;
	t_img		tex;
	int			i;

	tex = tex_view_by_player[e_NO];
	i = 0;
	while (++i < TEXMAX)
		if (i == ray->side)
			tex = tex_view_by_player[i];
	tex_x = (int)(wall_x * (double)tex.width);
	if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
		tex_x = tex.width - tex_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
		tex_x = tex.width - tex_x - 1;
	l->start = ray->draw_start;
	l->end = ray->draw_end;
	l->tex_x = tex_x;
	fill_text_vertically(l, tex, ray);
}

static void	_draw_ceiling_floor(t_line *l, t_raycast *ray)
{
	unsigned char const	*c = sglt()->map_info.ceiling;
	unsigned char const	*f = sglt()->map_info.floor;

	l->start = 0;
	l->end = ray->draw_start;
	fill_color_vertically(l, create_rgb(c[0], c[1], c[2]));
	l->start = ray->draw_end;
	l->end = W_HEIGHT;
	fill_color_vertically(l, create_rgb(f[0], f[1], f[2]));
}

void	drawing(t_raycast *ray)
{
	t_player const	ply = sglt()->player;
	t_line			l;
	double			wall_x;

	ft_bzero(&l, sizeof(t_line));
	l.l_x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wall_x = ply.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ply.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (sglt()->map_info.map[ray->map_y][ray->map_x] == '1')
		_draw_side(&l, wall_x, ray);
	_draw_ceiling_floor(&l, ray);
}
