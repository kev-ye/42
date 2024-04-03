/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 19:04:39 by kaye              #+#    #+#             */
/*   Updated: 2021/07/05 19:51:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

enum e_TEX
{
	e_WALL,
	e_EMPTY,
	e_COLLECT,
	e_EXIT,
	e_PLAYER
};

typedef struct s_tex
{
	char	tex_name;
	int		tex_id;
}	t_tex;

const t_tex	g_texture[] = {
	{'1', e_WALL},
	{'0', e_EMPTY},
	{'C', e_COLLECT},
	{'E', e_EXIT},
	{'P', e_PLAYER}
};

static void	draw_pix(int map_x, int map_y, int tex_id)
{
	const double	radio_x = ((double)WIDTH / singleton()->len_frame_x);
	const double	radio_y = ((double)HEIGTH / singleton()->len_frame_y);
	double			x;
	double			y;
	char			*ptr;

	y = 0.0;
	while (y < radio_y)
	{
		x = 0.0;
		while (x < radio_x)
		{
			ptr = singleton()->tex[tex_id].addr;
			ptr += (size_t)((y / radio_y)
					* singleton()->tex[tex_id].height)
				* singleton()->tex[tex_id].line_len;
			ptr += (size_t)((x / radio_x)
					* singleton()->tex[tex_id].width)
				* (singleton()->tex[tex_id].bpp / 8);
			pixel_put_color((map_x * radio_x) + x,
				(map_y * radio_y) + y, *(uint32_t *)ptr);
			++x;
		}
		++y;
	}
}

void	display_map(void)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (singleton()->map[y])
	{
		x = 0;
		while (singleton()->map[y][x])
		{
			i = 0;
			while (i < TEX_NBR - 1)
			{
				if (singleton()->map[y][x] == g_texture[i].tex_name)
				{
					draw_pix(x, y, g_texture[i].tex_id);
				}
				++i;
			}
			++x;
		}
		++y;
	}
}

void	display_player(void)
{
	draw_pix(singleton()->player.x, singleton()->player.y, 4);
}

void	display(void)
{
	display_map();
	display_player();
}

void	so_long(void)
{
	display();
	mlx_put_image_to_window(singleton()->mlx_ptr,
		singleton()->win_ptr, singleton()->img->img_ptr, 0, 0);
}
