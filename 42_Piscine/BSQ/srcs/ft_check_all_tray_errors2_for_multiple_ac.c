/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_all_tray_errors2_for_one.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:57:40 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 08:40:32 by wiozsert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_check_if_tray_is_full_of_obstacle(int *str)
{
	int		i;
	int		obstacle;

	i = 0;
	while (str[i] != '\n')
		i++;
	obstacle = str[i - 2];
	i++;
	while (str[i] == obstacle || str[i] == '\n')
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (1);
}

int		ft_check_if_char_is_missing(int *str, int obstacle, int empty)
{
	int		i;

	i = 0;
	while (str[i - 1] != '\n')
		i++;
	while (str[i] != '\n')
	{
		if (str[i] != obstacle && str[i] != empty && str[i] != '\n')
		{
			return (0);
		}
		else
			i++;
	}
	return (1);
}

int		ft_check_if_char_is_found(int *str, int empty, int obstacle)
{
	int i;

	i = 0;
	while (str[i] != '\n')
		i++;
	if ((str[i - 1] >= 0 && str[i - 1] <= 31) || (str[i - 1] == 127) ||
		(str[i - 2] >= 0 && str[i - 2] <= 31) || (str[i - 2] == 127) ||
		(str[i - 3] >= 0 && str[i - 3] <= 31) || (str[i - 3] == 127))
		return (0);
	if (str[i - 1] == str[i - 2] || str[i - 1] == str[i - 3] ||
		str[i - 2] == str[i - 3])
		return (0);
	else
		i += 1;
	while (str[i] != '\n')
	{
		if (str[i] != obstacle && str[i] != empty && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_if_line_are_same_length(int *str, int i, int j, int length)
{
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
		length++;
		j++;
	}
	while (str[i] != '\0')
	{
		if (length != j)
			return (0);
		else if (str[i] == '\n' && str[i + 1] == '\n')
			return (1);
		else
		{
			j = 0;
			i++;
			while (str[i] != '\n')
			{
				i++;
				j++;
			}
		}
	}
	return (1);
}

int		ft_check_if_tray_is_empy(int *str)
{
	int i;

	i = 0;
	while (str[i - 1] != '\n')
		i++;
	if (str[0] == '0')
		return (0);
	else if (str[i] == '\0' || str[i] == '\n')
		return (0);
	else
		return (1);
}
