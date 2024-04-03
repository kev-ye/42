/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:30:10 by kaye              #+#    #+#             */
/*   Updated: 2021/07/05 19:49:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	pixel_put_color(int x, int y, uint32_t color)
{
	char	*dst;

	dst = singleton()->img->addr
		+ (y * singleton()->img->line_len + x * (singleton()->img->bpp / 8));
	*(uint32_t *)dst = color;
}
