/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 12:44:06 by kaye              #+#    #+#             */
/*   Updated: 2020/08/23 19:52:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"

int			sep(char c, char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

int			words(char *str, char *charset)
{
	int		i;
	int		word;
	int		word_count;

	i = 0;
	word = 0;
	word_count = 0;
	while (str[i])
	{
		if (sep(str[i], charset))
			word = 0;
		if (word == 0 && (!sep(str[i], charset)))
		{
			word = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

int			l_w(char *str, char *charset, int i)
{
	int		size;

	size = 0;
	while (str[i])
	{
		if (!(sep(str[i], charset)))
		{
			size++;
		}
		i++;
	}
	return (size);
}

char		**split(char *str, char *sepa, char **tab)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	x = 0;
	y = 0;
	while (str[++i])
	{
		if (!(sep(str[i], sepa)))
		{
			if (y == 0)
				if (!(tab[x] = malloc(sizeof(char) * (l_w(str, sepa, i) + 1))))
					return (NULL);
			tab[x][y] = str[i];
			tab[x][y + 1] = '\0';
			y++;
		}
		if (sep(str[i], sepa) && y > 0)
		{
			x++;
			y = 0;
		}
	}
	return (tab);
}

char		**ft_split(char *str, char *charset)
{
	char	**tab;
	int		w;

	w = words(str, charset);
	if (!(tab = malloc(sizeof(char*) * (w + 1))))
		return (NULL);
	tab = split(str, charset, tab);
	tab[w] = NULL;
	return (tab);
}
