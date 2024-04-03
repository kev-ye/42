/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:01:34 by kaye              #+#    #+#             */
/*   Updated: 2021/03/01 16:09:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		get_color(char **s)
{
	int r;
	int g;
	int b;
	int color;

	r = ft_atoi(s[0]);
	g = ft_atoi(s[1]);
	b = ft_atoi(s[2]);
	if (r > 255 || g > 255 || b > 255)
		return (-1);
	color = create_rgb(r, g, b);
	return (color);
}

static int		check_color_amount(char **color, int count)
{
	if (count != 3)
	{
		free_split(color);
		return (-1);
	}
	return (1);
}

static int		check_color(char **color, int i)
{
	char	*str_trim;
	int		count;

	if (!(str_trim = ft_strtrim(color[i], " ")))
	{
		free_split(color);
		return (-1);
	}
	count = 0;
	while (str_trim[count])
	{
		if (!ft_isdigit(str_trim[count]))
		{
			free(str_trim);
			free_split(color);
			return (-1);
		}
		++count;
	}
	free(str_trim);
	return (1);
}

int				check_and_get_color(char *s)
{
	char	**color;
	int		count;
	int		c;

	count = 0;
	if (ft_charinstr(s, ',') != 2)
		return (-1);
	if (!(color = ft_split(s, ',')))
		return (-1);
	while (color[count] != NULL)
		++count;
	if (check_color_amount(color, count) == -1)
		return (-1);
	if (check_color(color, 0) == -1)
		return (-1);
	if (check_color(color, 1) == -1)
		return (-1);
	if (check_color(color, 2) == -1)
		return (-1);
	c = get_color(color);
	free_split(color);
	if (c == -1)
		return (-1);
	return (c);
}
