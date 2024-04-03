/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_gun_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:17:59 by kaye              #+#    #+#             */
/*   Updated: 2021/02/08 12:35:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		set_life_img(t_win *win, const char *path)
{
	if (!(win->life = malloc(sizeof(t_img))))
		return (0);
	ft_bzero(win->life, sizeof(t_img));
	if (!(win->life->img_ptr = mlx_xpm_file_to_image(win->mlx_ptr,
					(char *)path, &win->life->width, &win->life->height)))
		return (0);
	win->life->addr = mlx_get_data_addr(win->life->img_ptr,
			&win->life->bpp, &win->life->line_len, &win->life->endian);
	return (1);
}

int		set_gun_img(t_win *win, const char *path)
{
	if (!(win->gun = malloc(sizeof(t_img))))
		return (0);
	ft_bzero(win->gun, sizeof(t_img));
	if (!(win->gun->img_ptr = mlx_xpm_file_to_image(win->mlx_ptr,
					(char *)path, &win->gun->width, &win->gun->height)))
		return (0);
	win->gun->addr = mlx_get_data_addr(win->gun->img_ptr,
			&win->gun->bpp, &win->gun->line_len, &win->gun->endian);
	return (1);
}

void	life_bar(t_win *win)
{
	unsigned int	color;
	int				x;
	int				y;

	if (win->life->width > win->width || win->life->height > win->height)
		return ;
	x = 0;
	while (x < win->life->width)
	{
		y = 0;
		while (y < win->life->height)
		{
			color = *(unsigned int *)(win->life->addr +
					(y * win->life->line_len) + (x * (win->life->bpp / 8)));
			if (x < win->player_life * win->life->width && color != 0x000000FF)
				pixel_put_color(win->img, x, win->height - win->life->height
						+ y, color);
			++y;
		}
		++x;
	}
}

void	gun(t_win *win)
{
	unsigned int	color;
	int				x;
	int				y;

	if (win->gun->width > win->width || win->gun->height > win->height)
		return ;
	x = 0;
	while (x < win->gun->width)
	{
		y = 0;
		while (y < win->gun->height)
		{
			color = *(unsigned int *)(win->gun->addr +
					(y * win->gun->line_len) + (x * (win->gun->bpp / 8)));
			if (color != 0x0)
				pixel_put_color(win->img,
						x + (win->width - win->gun->width) / 2,
						y + (win->height - win->gun->height), color);
			++y;
		}
		++x;
	}
}
