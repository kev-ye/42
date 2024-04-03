/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infoConfigParsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:34:42 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:25:23 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define INFOMAX 6
#define CEILING 1
#define FLOOR 2

enum e_status
{
	e_NOCOMPLETE = 0,
	e_COMPLETE
};

typedef struct s_info
{
	int			i;
	int			id;
	char		*str;
	char const	*cf_id;
	size_t		start;
	size_t		end;
	size_t		info;
}	t_info;

static char const	*g_id[] = {
	"NO",
	"SO",
	"WE",
	"EA",
	"F",
	"C",
	NULL
};

BOOL	_info_check(t_info *info, int info_count[INFOMAX])
{
	int		i;

	i = 0;
	if (TRUE == get_info_parsing(info->str, info->id, info->info, info->cf_id))
		return (TRUE);
	while (NULL != g_id[i] && 1 == info->info)
	{
		if (0 == ft_strcmp(info->str, g_id[i]))
		{
			if (i < PATHMAX)
				info->id = i;
			else
				info->id = -1;
			if (i >= PATHMAX)
				info->cf_id = g_id[i];
			++info_count[i];
			free_clean((void **)&info->str);
			return (TRUE);
		}
		++i;
	}
	free_clean((void **)&info->str);
	return (FALSE);
}

BOOL	_info_line_check(char const *line, int info_count[INFOMAX])
{
	t_info	info;

	ft_bzero(&info, sizeof(t_info));
	info.id = -1;
	while ('\0' != line[info.i])
	{
		while ('\0' != line[info.i] && ' ' == line[info.i])
			++info.i;
		info.start = info.i;
		if (0 == info.info)
			while ('\0' != line[info.i] && ' ' != line[info.i])
				++info.i;
		else
			while ('\0' != line[info.i])
				++info.i;
		info.end = info.i;
		info.str = ft_substr(line, info.start, info.end - info.start);
		++info.info;
		if (FALSE == _info_check(&info, info_count))
			return (FALSE);
	}
	return (TRUE);
}

int	_status_check(int info_count[INFOMAX], char *config)
{
	int	i;

	i = 0;
	if (0 == config[0])
		return (e_NOCOMPLETE);
	if (FALSE == _info_line_check(config, info_count))
		exit_clean(E_ID, __FILE__, __LINE__);
	while (i < INFOMAX)
	{
		if (0 == info_count[i])
		{
			if (NULL == config)
				exit_clean(E_ID, __FILE__, __LINE__);
			printf(S_GREEN"CFG:%5c"S_NONE"%s\n", ' ', config);
			return (e_NOCOMPLETE);
		}
		if (info_count[i++] > 1)
			exit_clean(E_ID, __FILE__, __LINE__);
	}
	printf(S_GREEN"CFG:%5c"S_NONE"%s\n", ' ', config);
	return (e_COMPLETE);
}

int	info_config_parsing(void)
{
	static int	info_count[INFOMAX] = {0};
	char		**config;
	int			i;

	i = 0;
	config = sglt()->config;
	while (NULL != config && NULL != config[i])
	{
		if (e_COMPLETE == _status_check(info_count, config[i]))
			break ;
		++i;
	}
	if (0 == i)
		exit_clean(E_EMPTY, __FILE__, __LINE__);
	return (i + 1);
}
