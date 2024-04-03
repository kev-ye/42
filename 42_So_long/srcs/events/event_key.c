/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:24:21 by kaye              #+#    #+#             */
/*   Updated: 2021/07/05 20:04:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_move
{
	char	*key;
	int		x;
	int		y;
}	t_move;

enum	e_key
{
	e_W,
	e_S,
	e_A,
	e_D,
	e_KEY
};

const t_move	g_move[] = {
	{B_GREEN"W"NONE, 0, -1},
	{B_YELLOW"S"NONE, 0, 1},
	{B_RED"A"NONE, -1, 0},
	{B_PURPLE"D"NONE, 1, 0}
};

int	event_key_press(int keycode)
{
	const int	key[] = {KEY_CODE_W, KEY_CODE_S, KEY_CODE_A, KEY_CODE_D};
	int			i;

	i = 0;
	if (keycode == KEY_CODE_ESC)
		__exit__(NULL, NULL, NOTHING, SUCCESS);
	else
	{
		while (i < 4)
		{
			if (keycode == key[i] && singleton()->key_code[i] == 0)
				singleton()->key_code[i] = 1;
			++i;
		}
	}
	return (1);
}

int	event_key_release(int keycode)
{
	const int	key[] = {KEY_CODE_W, KEY_CODE_S, KEY_CODE_A, KEY_CODE_D};
	int			i;

	i = 0;
	if (keycode == KEY_CODE_ESC)
		__exit__(NULL, NULL, NOTHING, SUCCESS);
	else
	{
		while (i < 4)
		{
			if (keycode == key[i] && singleton()->key_code[i] == 1)
				singleton()->key_code[i] = 0;
			++i;
		}
	}
	return (1);
}

void	player_move(int i)
{
	if (singleton()->map[singleton()->player.y + g_move[i].y]
		[singleton()->player.x + g_move[i].x] != '1')
	{
		singleton()->player.x += g_move[i].x;
		singleton()->player.y += g_move[i].y;
		++singleton()->player.count;
		if (singleton()->map[singleton()->player.y]
			[singleton()->player.x] == 'C')
		{
			singleton()->map[singleton()->player.y]
		[singleton()->player.x] = '0';
			--singleton()->collectible;
		}
	}
	ft_printf("Player move : [%s]\n", g_move[i].key);
}

int	event_key(void)
{
	int	k;

	k = 0;
	if (singleton()->collectible == 0)
	{
		if (singleton()->map[singleton()->player.y]
			[singleton()->player.x] == 'E')
			__exit__(B_GREEN"WIN !"NONE, NULL, NOTHING, SUCCESS);
	}
	while (k < e_KEY)
	{
		if (singleton()->key_code[k] == 1)
			player_move(k);
		++k;
	}
	return (1);
}

int	init_key(void)
{
	int	i;

	i = 0;
	while (i < 4)
		singleton()->key_code[i++] = 0;
	return (1);
}
