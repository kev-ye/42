/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_music_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:44:00 by kaye              #+#    #+#             */
/*   Updated: 2021/02/09 10:52:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** clock(void) : Determine processor time used. Return -1 on error.
** Using in function game_soud_loop to play game music on loop.
*/

void	game_sound(void)
{
	system(SOUND" ./src_bonus/game_music/game_sound.wav 2>/dev/null&");
}

void	effect_sound_h(void)
{
	system(SOUND" ./src_bonus/game_music/health_sound.wav 2>/dev/null&");
}

void	effect_sound_m(void)
{
	system(SOUND" ./src_bonus/game_music/monster_sound.wav 2>/dev/null&");
}

void	play_game_sound(t_win *win)
{
	game_sound();
	win->sound_begin_time = clock();
}

void	game_sound_loop(t_win *win)
{
	clock_t time;

	time = clock();
	if (((double)(time - win->sound_begin_time) / CLOCKS_PER_SEC) > 15)
	{
		game_sound();
		win->sound_begin_time = time;
	}
}
