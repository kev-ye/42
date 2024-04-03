/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infoParsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:57:57 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:33:52 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_color_info
{
	int			i;
	int			color_index;
	char		*str;
	size_t		start;
	size_t		end;
}	t_color_info;

BOOL	_path_line_parsing(char *str)
{
	int	i;

	i = 0;
	while ('\0' != str[i])
	{
		if (FALSE == ft_isprint(str[i]) || TRUE == ft_isspace(str[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

BOOL	_color_line_parsing(char *str)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while ('\0' != str[i])
	{
		if (',' == str[i]
			|| TRUE == ft_isspace(str[i]) || TRUE == ft_isdigit(str[i]))
		{
			if (',' == str[i])
				++comma;
			++i;
		}
		else
			return (FALSE);
	}
	if (2 != comma)
		return (FALSE);
	return (TRUE);
}

BOOL	_fill_color(char *str, char const *cf_id, int color_index)
{
	t_cub3d		*ptr;
	uint32_t	color;

	ptr = sglt();
	if (ft_strlen(str) > 3)
		return (FALSE);
	color = ft_atoi(str);
	free_clean((void **)&str);
	if (color > 255)
		return (FALSE);
	if (0 == ft_strcmp(cf_id, "C"))
		ptr->map_info.ceiling[color_index] = color;
	else if (0 == ft_strcmp(cf_id, "F"))
		ptr->map_info.floor[color_index] = color;
	else
		return (FALSE);
	return (TRUE);
}

BOOL	_color_parsing(char *str, char const *cf_id)
{
	t_color_info	info;

	ft_bzero(&info, sizeof(t_color_info));
	if (FALSE == _color_line_parsing(str))
		return (FALSE);
	while ('\0' != str[info.i])
	{
		if (FALSE == ft_isdigit(str[info.i]))
		{
			++info.i;
			continue ;
		}
		info.start = info.i;
		while ('\0' != str[info.i] && TRUE == ft_isdigit(str[info.i]))
			++info.i;
		info.end = info.i;
		info.str = ft_substr(str, info.start, info.end - info.start);
		if (FALSE == _fill_color(info.str, cf_id, info.color_index))
			return (FALSE);
		++info.color_index;
	}
	return (TRUE);
}

BOOL	get_info_parsing(
	char *str,
	int const index,
	int const info,
	char const *cf_id
)
{
	t_cub3d	*ptr;

	ptr = sglt();
	if (2 != info || NULL == str)
		return (FALSE);
	if (-1 != index)
	{
		if (FALSE == _path_line_parsing(str))
			return (FALSE);
		ptr->map_info.path[index] = str;
	}
	else if (-1 == index)
	{
		if (FALSE == _color_parsing(str, cf_id))
			return (FALSE);
	}
	else
		return (FALSE);
	return (TRUE);
}
