/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawTools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:18:11 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:32:26 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_color_vertically(t_line *l, unsigned int const color)
{
	t_img const	*img = &sglt()->mlx_img;

	l->l_y = l->start;
	if (l->l_y >= 0)
	{
		while (l->l_y < l->end)
		{
			ft_memcpy(
				img->addr + l->l_y * img->size + l->l_x * (img->bpp / 8),
				&color,
				sizeof(unsigned int)
				);
			++l->l_y;
		}
	}
}

void	fill_text_vertically(t_line *l, t_img tex, t_raycast *ray)
{
	t_img const	*img = &sglt()->mlx_img;
	double		step;
	double		tex_pos;

	l->l_y = l->start;
	step = (double)tex.height / (double)ray->line_height;
	tex_pos = (l->l_y - W_HEIGHT / 2 + ray->line_height / 2) * step;
	if (l->l_y >= 0)
	{
		while (l->l_y < l->end)
		{
			l->tex_y = (int)tex_pos;
			tex_pos += step;
			ft_memcpy(
				img->addr + (l->l_y * img->size) + (l->l_x * (img->bpp / 8)),
				tex.addr + (l->tex_y * tex.size) + (l->tex_x * (tex.bpp / 8)),
				sizeof(unsigned int)
				);
			++l->l_y;
		}
	}
}
