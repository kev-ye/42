/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:42:20 by kaye              #+#    #+#             */
/*   Updated: 2021/03/01 19:09:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shut_down(t_win *win)
{
	if (!win->save)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win != NULL)
		free_win(win);
	exit(0);
}