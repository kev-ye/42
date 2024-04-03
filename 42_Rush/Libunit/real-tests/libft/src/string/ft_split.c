/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:58:10 by kaye              #+#    #+#             */
/*   Updated: 2021/03/09 19:52:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and returns an array of strings obtained by splitting s
** using the character c as a delimiter.
** the array must be ended by a NULL pointer.
** Returns NULL on error.
*/

static int	count_w(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (*s && *s != c)
			++count;
		while (*s && *s != c)
			++s;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;
	int		start;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	count = count_w(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	str[count] = NULL;
	i = 0;
	j = 0;
	while (i < count)
	{
		while (s[j] && s[j] == c)
			++j;
		start = j;
		while (s[j] && s[j] != c)
			++j;
		str[i++] = ft_substr(s, start, j - start);
	}
	return (str);
}
