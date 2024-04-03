/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tray_in_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 11:04:03 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 11:57:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		*ft_copy_tray_in_str(char *tray, int *str)
{
	int		fd;
	int		rd;
	int		i;
	char	c;

	rd = 1;
	i = 0;
	fd = open(tray, O_RDONLY);
	if (fd == -1)
		return (0);
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	close(fd);
	return (str);
}

static int		*ft_get_size_of_tray(char *tray, int *str)
{
	int		fd;
	int		rd;
	int		len;
	char	c;

	rd = 1;
	len = 0;
	fd = open(tray, O_RDONLY);
	if (fd == -1)
		return (0);
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		len++;
	}
	if (!(str = (int*)malloc(sizeof(int) * (len + 1))))
		return (NULL);
	close(fd);
	return (str);
}

int				*ft_init_str_from_file(char *tray, int *str)
{
	str = ft_get_size_of_tray(tray, str);
	str = ft_copy_tray_in_str(tray, str);
	return (str);
}
