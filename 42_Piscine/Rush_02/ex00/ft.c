/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 11:40:45 by kaye              #+#    #+#             */
/*   Updated: 2020/08/23 19:43:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int		ft_atoi(char *str)
{
	int i;
	int resultat;
	int signe;

	i = 0;
	resultat = 0;
	signe = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		i++;
	}
	return (resultat * signe);
}

int		to_find(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i + j] == to_find[j])
	{
		if (to_find[j + 1] == '\0'
				&& (str[i + j + 1] == ' ' || str[i + j + 1] == ':'))
			return (1);
		j++;
	}
	return (0);
}

void	ft_error(int error)
{
	if (error == 1)
		ft_putstr("Error\n");
	else if (error == 2)
		ft_putstr("Dict Error\n");
}
