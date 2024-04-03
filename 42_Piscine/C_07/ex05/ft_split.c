/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 15:38:45 by kaye              #+#    #+#             */
/*   Updated: 2020/08/20 13:58:36 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		is_word(char c, char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (0);
		i++;
	}
	return (1);
}

int		count_word(char *str, char *charset)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_word(str[i], charset))
			count++;
		while (str[i] && is_word(str[i], charset))
			i++;
		i++;
	}
	return (count);
}

char	*ft_malloc_word(char *str, char *charset, int place)
{
	char	*stock_str;
	int		i;
	int		len;
	int		place_i;

	i = 0;
	len = 0;
	place_i = place;
	while (str[place_i] != '\0' && is_word(str[place_i++], charset))
		len++;
	if (!(stock_str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[place] && is_word(str[place], charset))
	{
		stock_str[i] = str[place];
		i++;
		place++;
	}
	stock_str[i] = '\0';
	return (stock_str);
}

char	**ft_split(char *str, char *charset)
{
	int		place;
	int		index_str;
	int		word;
	int		count;
	char	**tab;

	index_str = 0;
	word = 0;
	count = count_word(str, charset);
	if (!(tab = (char**)malloc(sizeof(char*) * count + 1)))
		return (NULL);
	while (word < count)
	{
		while (str[index_str] && is_word(str[index_str], charset) == 0)
			index_str++;
		place = index_str;
		if (str[index_str] && is_word(str[index_str], charset) == 1)
			tab[word++] = ft_malloc_word(str, charset, place);
		while (str[index_str] && is_word(str[index_str], charset) == 1)
			index_str++;
	}
	tab[count] = NULL;
	return (tab);
}
