/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:06:03 by kaye              #+#    #+#             */
/*   Updated: 2020/08/10 19:34:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_is_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == 32)
		return (1);
	return (0);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_check_base(char *base)
{
	int		i;
	int		j;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+' || ft_is_space(base[i]))
			return (0);
		i++;
	}
	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_place_in_base(char nb, char *base)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (nb == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int		ft_atoi_base(char *str, char *base)
{
	int i;
	int resultat;
	int signe;
	int len_base;
	int place;

	i = 0;
	resultat = 0;
	signe = 0;
	len_base = ft_strlen(base);
	if (!(ft_check_base(base)))
		return (0);
	while (ft_is_space(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe++;
		i++;
	}
	signe = ((signe % 2) ? -1 : 1);
	while ((place = ft_place_in_base(str[i++], base)) >= 0)
		resultat = resultat * len_base + place;
	return (resultat * signe);
}
