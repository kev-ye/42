/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:01:56 by kaye              #+#    #+#             */
/*   Updated: 2021/02/24 16:37:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int				event_loop(t_win *win)
{
	if (!(ray_casting(win)))
		shut_down(win);
	mini_map(win);
	put_hud(win);
	game_sound_loop(win);
	event_key(win);
	return (1);
}

int				event_destroy_win(t_win *win)
{
	shut_down(win);
	return (1);
}
