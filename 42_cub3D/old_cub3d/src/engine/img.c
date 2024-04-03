/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:09:17 by kaye              #+#    #+#             */
/*   Updated: 2021/02/24 15:54:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_color(
		t_line *line,
		t_win *win,
		unsigned int color)
{
	line->line_y = line->draw_start;
	if (line->line_y >= 0)
	{
		while (line->line_y < line->draw_end)
		{
			ft_memcpy(win->img->addr + line->line_y * win->img->line_len
			+ line->line_x * (win->img->bpp / 8), &color, sizeof(unsigned int));
			++line->line_y;
		}
	}
}

void	draw_vertical_tex(
		t_line *line,
		t_win *win,
		t_img *texture,
		t_ray_cast *ray)
{
	double step;
	double texpos;

	line->line_y = line->draw_start;
	step = (double)texture->height / (double)ray->line_height;
	texpos = (line->line_y - win->height / 2 + ray->line_height / 2) * step;
	if (line->line_y >= 0)
	{
		while (line->line_y++ < line->draw_end)
		{
			line->tex_y = (int)texpos;
			texpos += step;
			ft_memcpy(win->img->addr + line->line_y * win->img->line_len
			+ line->line_x * win->img->bpp / 8,
			texture->addr + line->tex_y * texture->line_len
			+ line->tex_x * (texture->bpp / 8), sizeof(unsigned int));
		}
	}
}

t_img	*new_image(
		t_win *win,
		int size_width,
		int size_height)
{
	t_img *new_img;

	if (!(new_img = malloc(sizeof(t_img))))
		return (NULL);
	ft_bzero(new_img, sizeof(t_img));
	if (!(new_img->img_ptr = mlx_new_image(win->mlx_ptr, size_width,
					size_height)))
		return (NULL);
	new_img->addr = mlx_get_data_addr(new_img->img_ptr, &new_img->bpp,
			&new_img->line_len, &new_img->endian);
	new_img->width = size_width;
	new_img->height = size_height;
	return (new_img);
}
