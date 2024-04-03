/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapParsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:52:30 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 23:18:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_check
{
	int		v;
	int		h;
	BOOL	edge1;
	BOOL	edge2;
}	t_check;

static void	_condition_adapt(BOOL const cond1, BOOL const cond2)
{
	if (TRUE == cond1 && TRUE == cond2)
		return ;
	exit_clean(E_SURROUND, __FILE__, __LINE__);
}

static void	_horizontal_check2(
	char const *line,
	int const h_pos,
	t_check *check
)
{
	check->h = h_pos;
	while ('\0' != line[check->h])
	{
		if (line[check->h] == ' ')
			break ;
		if (line[check->h++] == '1')
		{
			check->edge2 = TRUE;
			break ;
		}
	}
}

static void	_vertical_check2(
	char **map,
	int const v_pos,
	int const h_pos,
	t_check *check
)
{
	check->v = v_pos;
	while (NULL != map[check->v])
	{
		if (h_pos <= (int)ft_strlen(map[check->v])
			&& (map[check->v][h_pos] == ' ' || map[check->v][h_pos] == '\0'))
			break ;
		if (h_pos <= (int)ft_strlen(map[check->v])
			&& map[check->v][h_pos] == '1')
		{
			check->edge2 = TRUE;
			break ;
		}
		if (h_pos > (int)ft_strlen(map[check->v]))
			break ;
		++check->v;
	}
}

void	horizontal_check(char const *line, int const h_pos)
{
	t_check	check;

	if ('1' == line[h_pos] || ' ' == line[h_pos])
		return ;
	ft_bzero(&check, sizeof(t_check));
	check.h = h_pos;
	while (-1 != check.h)
	{
		if (line[check.h] == ' ')
			break ;
		if (line[check.h--] == '1')
		{
			check.edge1 = TRUE;
			break ;
		}
	}
	_horizontal_check2(line, h_pos, &check);
	_condition_adapt(check.edge1, check.edge2);
}

void	vertical_check(char **map, int const v_pos, int const h_pos)
{
	t_check	check;

	if ('1' == sglt()->map_info.map[v_pos][h_pos]
		|| ' ' == sglt()->map_info.map[v_pos][h_pos])
		return ;
	ft_bzero(&check, sizeof(t_check));
	check.v = v_pos;
	while (-1 != check.v)
	{
		if (h_pos <= (int)ft_strlen(map[check.v])
			&& (map[check.v][h_pos] == ' ' || map[check.v][h_pos] == '\0'))
			break ;
		if (h_pos <= (int)ft_strlen(map[check.v]) && map[check.v][h_pos] == '1')
		{
			check.edge1 = TRUE;
			break ;
		}
		if (h_pos > (int)ft_strlen(map[check.v]))
			break ;
		--check.v;
	}
	_vertical_check2(map, v_pos, h_pos, &check);
	_condition_adapt(check.edge1, check.edge2);
}
