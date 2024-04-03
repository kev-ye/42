/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:49:09 by kaye              #+#    #+#             */
/*   Updated: 2021/12/12 19:44:40 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

typedef struct s_norm
{
	t_hr		*ptr;
	uint64_t	to_get;
	uint64_t	i;
	int			ret;
}	t_norm;

static void	_save_data(size_t to_save, char *key_or_mapped)
{
	t_hr	*ptr;

	ptr = sgt();
	if (to_save % 2 == 1)
		ptr->data.key = key_or_mapped;
	else
		set_map(ptr->data.key, key_or_mapped);
}

void	to_o(void)
{
	t_hr	*ptr;
	int		i;

	ptr = sgt();
	i = 0;
	while (ptr->buff[i])
	{
		if (ptr->buff[i] == '\n')
			ptr->buff[i] = '\0';
		++i;
	}
	ptr->len = i;
}

BOOL	check_if_double_o(char *str)
{
	if (!str[0])
		return (TRUE);
	return (FALSE);
}

BOOL	get_data(void)
{
	t_norm	value;

	ft_bzero(&value, sizeof(t_norm));
	value.ptr = sgt();
	value.ptr->buff = malloc(MALLOC_SIZE);
	if (value.ptr->buff == NULL)
		return (FALSE);
	value.ret = read(STDIN_FILENO, value.ptr->buff, MALLOC_SIZE);
	if (value.ret < 0)
		return (FALSE);
	value.ptr->buff[value.ret] = '\0';
	to_o();
	value.to_get = 1;
	while (value.i < value.ptr->len)
	{
		_save_data(value.to_get, value.ptr->buff + value.i);
		++value.to_get;
		value.i += ft_strlen(value.ptr->buff + value.i) + 1;
		if (check_if_double_o(value.ptr->buff + value.i) == TRUE)
		{
			value.ptr->save_index = ++value.i;
			break ;
		}
	}
	return (TRUE);
}
