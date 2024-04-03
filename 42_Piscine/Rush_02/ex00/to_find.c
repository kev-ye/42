/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessakhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:46:14 by aessakhi          #+#    #+#             */
/*   Updated: 2020/08/23 20:41:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"

int		ft_strlentab(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			j++;
		i++;
	}
	return (i);
}

int		wordsentry(char *str, char *charset)
{
	int		i;
	int		word;
	int		word_count;

	i = 0;
	word = 0;
	word_count = 0;
	while (str[i] != ':')
		i++;
	i++;
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

int		l_entry(char *str, char *charset, int i)
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

char	**split_entry(char *str, char *sepa, char **tab)
{
	t_variable var;

	var.i = 0;
	var.x = 0;
	var.y = 0;
	while (str[var.i] != ':')
		var.i++;
	while (str[++var.i])
	{
		if (!(sep(str[var.i], sepa)))
		{
			if (var.y == 0)
				tab[var.x] = malloc_tab(str, sepa, var.i);
			tab[var.x][var.y] = str[var.i];
			tab[var.x][var.y + 1] = '\0';
			var.y++;
		}
		if (sep(str[var.i], sepa) && var.y > 0)
		{
			var.x++;
			var.y = 0;
		}
	}
	return (tab);
}

char	**ft_split2(char *str, char *charset)
{
	char	**tab;
	int		w;

	w = wordsentry(str, charset);
	if (!(tab = malloc(sizeof(char*) * (w + 1))))
		return (NULL);
	tab = split_entry(str, charset, tab);
	tab[w] = 0;
	return (tab);
}
